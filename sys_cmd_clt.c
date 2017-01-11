#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in ser_addr;
	int in_char , send_char;

	if (argc < 2) {
		printf("sys_cmd_clt:Please Input the message.\n");
		exit(0);
	}

	in_char = strlen(argv[1]);

	if (in_char > 15) {
		printf("sys_cmd_clt:Too long message(should less than or equal to 15 characters).\n");
		exit(1);	
	}
	
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sockfd < 0) {
		printf("sys_cmd_clt:Fail to create sock.\n");
		exit(1);
	}
	
	memset(&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	ser_addr.sin_port = htons(4000);
	
	printf("sys_cmd_clt:Send buf =>%s\n" , argv[1]);
	
	send_char = sendto(sockfd,argv[1],strlen(argv[1]),0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	if (send_char != in_char) {
		printf("sys_cmd_clt:Fail!\n");
		close(sockfd);
		exit(1);
	}
	
	close(sockfd);

	return 0;
}
