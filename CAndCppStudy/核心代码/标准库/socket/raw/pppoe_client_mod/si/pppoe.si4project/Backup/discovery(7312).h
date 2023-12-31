#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <linux/sockios.h>
#include <string.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>	
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "md5.h"


#define MAC_LEN 6 //the length of a mac address
#define MTU 1500
#define ETHER_TYPE_DISCOVERY 0x8863
#define ETHER_TYPE_PPP_SESSION 0x8864
#define ETH_HEARER_LEN_WITHOUT_CRC 14
#define PPPOE_HEADER_LEN 6

#define Service_Name 0x0101
#define Host_Uniq 0x0103
#define Ac_Name 0x0102

#define CODE_OF_PADI 0x09
#define CODE_OF_PADO 0x07
#define CODE_OF_PADR 0x19
#define CODE_OF_PADS 0x65
#define CODE_OF_PPP_SESSION 0x00
#define LCP 0xc021
#define PAP 0xc023
#define CHAP 0xc223
#define IPCP 0x8021
#define TIME_OUT_DISCOVERY 5
#define TIME_OUT_SESSION 5

extern char *NIC;  //name of the interface to be used
extern unsigned short int clients;  //the number if clients to be forked
extern int ifindex;
extern int discovery_socket;
extern int session_socket;
	
struct pppoe_packet {
    // mac head
	char eth_dst_mac[MAC_LEN];
	char eth_src_mac[MAC_LEN];
	unsigned short int eth_type;
    //pppoe head
	char pppoe_type:4;
	char pppoe_ver:4;
	unsigned char pppoe_code;
	unsigned short  pppoe_session_id;  //network order
	unsigned short  pppoe_length; //the length of pppoe payload
	//pppoe data
	char payload[MTU-ETH_HEARER_LEN_WITHOUT_CRC-PPPOE_HEADER_LEN];
};

struct Connection_info {
	char my_mac[MAC_LEN];
	char peer_mac[MAC_LEN];
	int index; //which client am i
	int discovery_succeed;
	int dial_in_complete;
	unsigned short int host_uniq; //16bit by design,no limit in RFC,in host order
	unsigned short int pppoe_session_id; //network order
	unsigned int LCP_magic_number; //network order
};

struct PPPOE_TAG {
	unsigned short int TAG_TYPE; // 2 bytes
	unsigned short int TAG_LENGTH;//2 
	unsigned char TAG_VALUE[MTU-ETH_HEARER_LEN_WITHOUT_CRC-PPPOE_HEADER_LEN-4];
};

struct ppp_frame_for_pppoe {
	unsigned short Protocol_Field; //identifies the datagram encapsulated in the Information field
	char Information[MTU-ETH_HEARER_LEN_WITHOUT_CRC-PPPOE_HEADER_LEN-2];
};

struct LCP_packet {
	unsigned char Code;
	unsigned char Identifier;
	unsigned short Length; //indicates the length of the LCP packet, including the Code, Identifier, Length and Data fields
	char Data[MTU-ETH_HEARER_LEN_WITHOUT_CRC-PPPOE_HEADER_LEN-4-2];
};

struct magic_number {
	unsigned char Type;
	unsigned char Length;
	unsigned int Data;
};

struct MRU {
	unsigned char Type;
	unsigned char Length;
	unsigned short int Data;
};

struct PFC {
    unsigned char type;
    unsigned char length;
};

struct PAP_data_1{
    unsigned char user_length;
    unsigned char user_name[1];
};

struct PAP_data_2{
    unsigned char passwd_length;
    unsigned char passwd[1];
};

/*
char a[4096];
struct PAP_data_1 * p1 =a;
p1->user_length =len;
memcpy(p1->user_name,user,p1->user_length);
struct PAP_data_2 * p2 = a+p1->user_length+1;
p2->passwd_length = len2;
memcpy(p2->passwd,passwd,p2->passwd);
write(sockfd , a,p1->user_length+p2->passwd_length+2);
*/

struct CHAP_value {
	unsigned char Value_size;
	unsigned char Value[16];
	unsigned char Name[4];//we asume that the name of pppoe account is always 4 bytes
};

struct IPCP_ip_address {
	unsigned char type;
	unsigned char length;
	unsigned char data[4];
};
