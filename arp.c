#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/ether.h>

#include "arp_func.h"

int main(int argc, char *argv[]){
	int sock;

	/*raw socketを設定する*/
	if((sock = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ARP))) == -1){ 
		perror("socket");
		exit(-1);
	}
	
	/*ARP要求の設定*****************************************************/
	memcpy(eth_hed.ether_dhost,ether_aton("ff:ff:ff:ff:ff:ff"), 
				sizeof(eth_hed.ether_dhost));
	memcpy(eth_hed.ether_shost,ether_aton(argv[3]),
				sizeof(eth_hed.ether_shost));
	eth_hed.ether_type = htons(ETHERTYPE_ARP);

	arp_arp.arp_hrd = htons(ARPHRD_ETHER);	
	arp_arp.arp_pro = htons(ETHERTYPE_IP); 
	arp_arp.arp_hln = MAC_LEG;
	arp_arp.arp_pln = IP_LEG;
	arp_arp.arp_op  = htons(ARPOP_REQUEST);
	
	memcpy(arp_arp.arp_sha,eth_hed.ether_shost,sizeof(arp_arp.arp_sha));
	inet_aton(argv[1],(struct in_addr *)arp_arp.arp_spa);
	memcpy(arp_arp.arp_tha,eth_hed.ether_dhost,sizeof(arp_arp.arp_tha));
	inet_aton(argv[2],(struct in_addr *)arp_arp.arp_tpa);	
	
	/*設定したARP要求の送信*/
	send_packet(sock,&packet);

	/*ARP応答の受信*/
	if(recv(sock,&packet,sizeof(ARP_req),0) < 0){
		perror("recv\n");
		exit(-1);
	}
	/*ARP応答から取得したMACアドレスを表示*/
	printf("dest MAC adress : %s\n",ether_ntoa((struct ether_addr *)&eth_hed.ether_shost));
	
	return 0;
}



