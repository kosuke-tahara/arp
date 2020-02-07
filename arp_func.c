#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include "arp_func.h"

void send_packet(int sock,ARP_req *packet){
	struct sockaddr_ll sock_ll;
	unsigned char ret;
	
	bzero(&sock_ll,sizeof(sock_ll));
	sock_ll.sll_family  = AF_PACKET;
  	sock_ll.sll_halen   = 6; 
	/*ネットワークインターフェースの設定なので環境に応じて変更する ifconfigで調べることが可能*/
	sock_ll.sll_ifindex = if_nametoindex("ens33");
  	memset(&sock_ll.sll_addr, 0xff, 6);

	if(sendto(sock,packet,sizeof(ARP_req),0,(struct sockaddr *)&sock_ll,sizeof(sock_ll)) == -1){
		perror("send_packet");
		exit(-1);
	}
}
