#include "my_socket_ts.h"
	
int
create_recv_socket_ts(char* inf, int port_no)                                                       
{                                                                               
    int s;                 
    int so_timestamping_flags = 0; 
    int so_timestamp = 0;                                                       
    int so_timestampns = 0;
    int enabled = 1;
    int val;                                                                    
    socklen_t len;

    struct ifreq hwtstamp;                                                      
    struct hwtstamp_config hwconfig, hwconfig_requested;                        
    struct sockaddr_in addr; 
    
     
    //This should go in config
    so_timestamping_flags |= SOF_TIMESTAMPING_RX_SOFTWARE;                      
    so_timestamping_flags |= SOF_TIMESTAMPING_SOFTWARE;                                                   
  
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);   
    if (s == -1)                                                            
    {                                                                       
        printf("ERROR: socket(). Exiting...\n");                        
        perror("SOCKET:");                                              
        exit(1);                                                        
    }   
    //set_socket_inf(s, inf, socket_address);
    setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, inf, strlen(inf));  
    
    
    memset(&hwtstamp, 0, sizeof(hwtstamp));                                     
    strncpy(hwtstamp.ifr_name, inf, sizeof(hwtstamp.ifr_name));           
    hwtstamp.ifr_data = (void *)&hwconfig;                                      
    memset(&hwconfig, 0, sizeof(hwconfig));                                     
    hwconfig.tx_type =                                                          
        (so_timestamping_flags & SOF_TIMESTAMPING_TX_HARDWARE) ?                
        HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;                                       
    hwconfig.rx_filter =                                                        
        (so_timestamping_flags & SOF_TIMESTAMPING_RX_HARDWARE) ?                
        HWTSTAMP_FILTER_PTP_V1_L4_SYNC : HWTSTAMP_FILTER_NONE;                  
    hwconfig_requested = hwconfig;                                              
    if (ioctl(s, SIOCSHWTSTAMP, &hwtstamp) < 0) {                            
        if ((errno == EINVAL || errno == ENOTSUP) &&                            
            hwconfig_requested.tx_type == HWTSTAMP_TX_OFF &&                    
            hwconfig_requested.rx_filter == HWTSTAMP_FILTER_NONE)               
            printf("SIOCSHWTSTAMP: disabling hardware time stamping not possible\n");
        else{                                                                               
            printf("SIOCSHWTSTAMP: %s\n", strerror(errno));                                 
            exit(1);                                                                    
        }                                                                     
    }                                                                           
    printf("SIOCSHWTSTAMP: tx_type %d requested, got %d; rx_filter %d requested, got %d\n",
           hwconfig_requested.tx_type, hwconfig.tx_type,                        
           hwconfig_requested.rx_filter, hwconfig.rx_filter);    
    
    addr.sin_family = AF_INET;                                                  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);                                   
    addr.sin_port = htons(port_no);      
    if (bind(s,                                                              
         (struct sockaddr *)&addr,                                              
         sizeof(struct sockaddr_in)) < 0){
        printf("bind: %s\n", strerror(errno));                                 
        exit(1);
    } 
    


    if (so_timestamp &&                                                         
        setsockopt(s, SOL_SOCKET, SO_TIMESTAMP,                              
               &enabled, sizeof(enabled)) < 0){
        printf("setsockopt SO_TIMESTAMP: %s\n", strerror(errno));
        exit(1);
    }                                  
                                                                                
    if (so_timestampns &&                                                       
        setsockopt(s, SOL_SOCKET, SO_TIMESTAMPNS,                            
               &enabled, sizeof(enabled)) < 0){
        printf("setsockopt SO_TIMESTAMPNS: %s\n", strerror(errno));
        exit(1);
    }                                  
                                                                                
    if (so_timestamping_flags &&                                                
        setsockopt(s, SOL_SOCKET, SO_TIMESTAMPING,                           
               &so_timestamping_flags,                                          
               sizeof(so_timestamping_flags)) < 0){
        printf("setsockopt SO_TIMESTAMPING: %s\n", strerror(errno));
        exit(1);
    }                              
                                                                                
    /* request IP_PKTINFO for debugging purposes */                             
    if (setsockopt(s, SOL_IP, IP_PKTINFO,                                    
               &enabled, sizeof(enabled)) < 0)                                  
        printf("%s: %s\n", "setsockopt IP_PKTINFO", strerror(errno));                                                          


    /* verify socket options */                                                 
    len = sizeof(val);                                                          
    if (getsockopt(s, SOL_SOCKET, SO_TIMESTAMP, &val, &len) < 0)             
        printf("%s: %s\n", "getsockopt SO_TIMESTAMP", strerror(errno));         
    else                                                                        
        printf("SO_TIMESTAMP %d\n", val);                                       
                                                                                
    if (getsockopt(s, SOL_SOCKET, SO_TIMESTAMPNS, &val, &len) < 0)           
        printf("%s: %s\n", "getsockopt SO_TIMESTAMPNS",                         
               strerror(errno));                                                
    else                                                                        
        printf("SO_TIMESTAMPNS %d\n", val);                                     
                                                                                
    if (getsockopt(s, SOL_SOCKET, SO_TIMESTAMPING, &val, &len) < 0) {        
        printf("%s: %s\n", "getsockopt SO_TIMESTAMPING",                        
               strerror(errno));                                                
    } else {                                                                    
        printf("SO_TIMESTAMPING %d\n", val);                                    
        if (val != so_timestamping_flags)                                       
            printf("   not the expected value %d\n",                            
                   so_timestamping_flags);                                      
    }                                          

  
    return s;                                                               
} 
void
setup_msghdr(struct msghdr* msg, struct iovec* entry, struct control* control, 
            char *payload, int payload_len, struct sockaddr_in* from_addr)
{
    memset(msg, 0, sizeof(struct msghdr));
    msg->msg_iov = entry;                                                       
    msg->msg_iovlen = 1;                                                         
    entry->iov_base = payload;                                                      
    entry->iov_len = payload_len;                                               
    msg->msg_name = (caddr_t)from_addr;                                         
    msg->msg_namelen = sizeof(struct sockaddr_in);                                        
    msg->msg_control = control;                                                 
    msg->msg_controllen = sizeof(struct control);    
}

int 
recv_packet_ts(int s, struct msghdr* msg, int recvmsg_flags)
{
    int i;
    int res;
    res = recvmsg(s, msg, 0);
    printf("In recvpacket after recvmsg\n");
    if (res < 0) {
        printf("%s %s: %s\n",
               "recvmsg",
               (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
               strerror(errno));
    } else {
        //printpacket(&msg, res, payload,
        //        s, recvmsg_flags);
        if ((recvmsg_flags & MSG_ERRQUEUE) == 0){
            /*printf("after:regular:data:\n");
            for (i = 0; i < 256; i++)
            {
                printf("0x%x\t",(uint8_t)*(data+i));
            }
            printf("\n");*/
        }
        else{
            printf("Received error packet\n");
        }
    }

}

void 
printpacket(struct msghdr *msg, int res,
            char *data,	int sock, int recvmsg_flags)
{
	struct sockaddr_in *from_addr = (struct sockaddr_in *)msg->msg_name;
	struct cmsghdr *cmsg;
	struct timeval tv;
	struct timespec ts;
	struct timeval now;

	gettimeofday(&now, 0);

	printf("%ld.%06ld: received %s data, %d bytes from %s, %zu bytes control messages\n",
	       (long)now.tv_sec, (long)now.tv_usec,
	       (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
	       res,
	       inet_ntoa(from_addr->sin_addr),
	       msg->msg_controllen);
	if ((recvmsg_flags & MSG_ERRQUEUE) == 0){
		printf("Data Data Data\n");
		printf("Data:%u\n",*(uint8_t*)data);
	}
	for (cmsg = CMSG_FIRSTHDR(msg);
	     cmsg;
	     cmsg = CMSG_NXTHDR(msg, cmsg)) {
		printf("   cmsg len %zu: ", cmsg->cmsg_len);
		switch (cmsg->cmsg_level) {
		case SOL_SOCKET:
			printf("SOL_SOCKET ");
			switch (cmsg->cmsg_type) {
			case SO_TIMESTAMP: {
				struct timeval *stamp =
					(struct timeval *)CMSG_DATA(cmsg);
				printf("SO_TIMESTAMP %ld.%06ld",
				       (long)stamp->tv_sec,
				       (long)stamp->tv_usec);
				break;
			}
			case SO_TIMESTAMPNS: {
				struct timespec *stamp =
					(struct timespec *)CMSG_DATA(cmsg);
				printf("SO_TIMESTAMPNS %ld.%09ld",
				       (long)stamp->tv_sec,
				       (long)stamp->tv_nsec);
				break;
			}
			case SO_TIMESTAMPING: {
				struct timespec *stamp =
					(struct timespec *)CMSG_DATA(cmsg);
				printf("SO_TIMESTAMPING ");
				printf("SW %ld.%09ld ",
				       (long)stamp->tv_sec,
				       (long)stamp->tv_nsec);
				stamp++;
				/* skip deprecated HW transformed */
				stamp++;
				printf("HW raw %ld.%09ld",
				       (long)stamp->tv_sec,
				       (long)stamp->tv_nsec);
				break;
			}
			default:
				printf("type %d", cmsg->cmsg_type);
				break;
			}
			break;
		case IPPROTO_IP:
			printf("IPPROTO_IP ");
			switch (cmsg->cmsg_type) {
			case IP_RECVERR: {
				struct sock_extended_err *err =
					(struct sock_extended_err *)CMSG_DATA(cmsg);
				printf("IP_RECVERR ee_errno '%s' ee_origin %d => %s",
					strerror(err->ee_errno),
					err->ee_origin,
#ifdef SO_EE_ORIGIN_TIMESTAMPING
					err->ee_origin == SO_EE_ORIGIN_TIMESTAMPING ?
					"bounced packet" : "unexpected origin"
#else
					"probably SO_EE_ORIGIN_TIMESTAMPING"
#endif
					);
				if (res < sizeof(sync))
					printf(" => truncated data?!");
				else if (!memcmp(sync, data + res - sizeof(sync),
							sizeof(sync)))
					printf(" => GOT OUR DATA BACK (HURRAY!)");
				break;
			}
			case IP_PKTINFO: {
				struct in_pktinfo *pktinfo =
					(struct in_pktinfo *)CMSG_DATA(cmsg);
				printf("IP_PKTINFO interface index %u",
					pktinfo->ipi_ifindex);
				break;
			}
			default:
				printf("##############type %d", cmsg->cmsg_type);
				break;
			}
			break;
		default:
			printf("level %d type %d",
				cmsg->cmsg_level,
				cmsg->cmsg_type);
			break;
		}
		printf("\n");
	}
}





/*


int
inf_to_index(char* inf)
{
	int inf_indx;
	if ((inf_indx = if_nametoindex (inf)) == 0){                   
		printf("Failed to get interface index of \'%s\'\n",inf);                                                
		perror ("if_nametoindex():");      
		exit (EXIT_FAILURE);                                                
	}
    return inf_indx;
}
*/ 
