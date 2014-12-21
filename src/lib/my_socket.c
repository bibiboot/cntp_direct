#include "my_socket.h"
	
int
create_sending_socket(char* inf, struct sockaddr_ll* socket_address)                                                       
{                                                                               
    int s;                                                                  
    s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));                      
    if (s == -1)                                                            
    {                                                                       
        printf("ERROR: socket(). Exiting...\n");                        
        perror("SOCKET:");                                              
        exit(1);                                                        
    }   
    set_socket_inf(s, inf, socket_address);                                                                    
    return s;                                                               
} 

void
set_socket_inf(int s, char* inf, struct sockaddr_ll* socket_address)
{
	socket_address->sll_family   = PF_PACKET;                                    
    socket_address->sll_protocol = htons(ETH_P_IP);                              
    socket_address->sll_ifindex  = inf_to_index(inf);
}

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
