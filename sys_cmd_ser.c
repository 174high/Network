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
	int recv_len;
	char recv_buf[16];
	unsigned int addr_len = sizeof(struct sockaddr_in);

	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockfd < 0) {
		printf("sys_cmd_ser:Fail to create socket.\n");
		exit(0);
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	ser_addr.sin_port = htons(4000);

	if(bind(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0) {
		printf("sys_cmd_ser:Fail to bind socket and address.\n");
		close(sockfd);
		exit(1);
	}

	printf("sys_cmd_ser is running...\n");

	while(1) {
		memset(&recv_buf, 0, sizeof(recv_buf));

		recv_len = recvfrom(sockfd,recv_buf,16,0,(struct sockaddr*)&ser_addr,&addr_len);
		if(recv_len <0) {
			printf("sys_cmd_ser:Fail to recvfrom().\n");
			close(sockfd);
			exit(1);
		} else if (0 == recv_len)
			continue;
		else {
			printf("sys_cmd_ser:recv_buf=%s\n" , recv_buf);
			if (!strcmp(recv_buf, "on"))
				system("service call bluetooth_manager 6 >> /data/harrytest11.txt");
			else if (!strcmp(recv_buf, "off"))
				system("service call bluetooth_manager 8 > /data/harrytest11.txt");
			else
				continue;
		}
	}

	return 0;
}
