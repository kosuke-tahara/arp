#ifndef ARP_H
#define ARP_H

typedef struct ARP_req{
	struct ether_header eth_hed;
	struct ether_arp eth_arp;
}ARP_req;

ARP_req packet;

#define eth_hed packet.eth_hed
#define arp_arp packet.eth_arp
#define MAC_LEG 0x06
#define IP_LEG  0x04

void send_packet(int sock,ARP_req *packet);

#endif
