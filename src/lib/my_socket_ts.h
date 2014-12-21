#include "globals.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <linux/if_ether.h> 
#include <linux/if_packet.h>

#include <errno.h>                                                              
#include <string.h>                                                             
                                                                                
//#include <sys/time.h>                                                           
#include <sys/socket.h>                                                         
//#include <sys/select.h>                                                         
#include <sys/ioctl.h>                                                          
#include <arpa/inet.h>                                                          
#include <net/if.h>                                                             
                                                                                
#include <asm/types.h>                                                          
#include <linux/net_tstamp.h>                                                   
#include <linux/errqueue.h>



#ifndef SO_TIMESTAMPING                                                         
# define SO_TIMESTAMPING         37                                             
# define SCM_TIMESTAMPING        SO_TIMESTAMPING                                
#endif                                                                          
                                                                                
#ifndef SO_TIMESTAMPNS                                                          
# define SO_TIMESTAMPNS 35                                                      
#endif                                                                          
                                                                                
#ifndef SIOCGSTAMPNS                                                            
# define SIOCGSTAMPNS 0x8907                                                    
#endif                                                                          
                                                                                
#ifndef SIOCSHWTSTAMP                                                           
# define SIOCSHWTSTAMP 0x89b0                                                   
#endif  

struct control{                                                                    
    struct cmsghdr cm;                                                      
    char control[512];                                                      
};            
int create_recv_socket_ts(char*, int port_no);
void setup_msghdr(struct msghdr* , 
                  struct iovec* , 
                  struct control* ,  
                  char *, 
                  int, 
                  struct sockaddr_in* );
int recv_packet_ts(int, struct msghdr* msg, int);
void printpacket(struct msghdr *, int, char *, int, int);
//void set_socket_inf(int, char*, struct sockaddr_ll*);
//int inf_to_index(char*);
