#include <sys/socket.h>
#include <linux/netlink.h>
#include <string.h>
#include <stdio.h>

#define MY_GROUP    1

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_nl user_sockaddr;
	struct nlmsghdr *nl_msghdr;
	struct msghdr msghdr;
	struct iovec iov;

	char* kernel_msg;

	sockfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
	if(sockfd < 0) {
		printf("user_service_nl:Fail to create socket.\n");
		exit(0);
	}

	memset(&user_sockaddr, 0, sizeof(user_sockaddr));
	user_sockaddr.nl_family = AF_NETLINK;
	user_sockaddr.nl_pid = getpid();
	user_sockaddr.nl_groups = MY_GROUP; 

	bind(sockfd, (struct sockaddr*)&user_sockaddr, sizeof(user_sockaddr));
	while (1) {
		nl_msghdr = (struct nlmsghdr*) malloc(NLMSG_SPACE(256));
		memset(nl_msghdr, 0, NLMSG_SPACE(256));

		iov.iov_base = (void*) nl_msghdr;
		iov.iov_len = NLMSG_SPACE(256);

		msghdr.msg_name = (void*) &user_sockaddr;
		msghdr.msg_namelen = sizeof(user_sockaddr);
		msghdr.msg_iov = &iov;
		msghdr.msg_iovlen = 1;

		recvmsg(sockfd, &msghdr, 0);

		kernel_msg = (char*)NLMSG_DATA(nl_msghdr);
		printf("Kernel message: %s\n", kernel_msg); // print to android logs
	}

	close(sockfd);

	return 0;
}
