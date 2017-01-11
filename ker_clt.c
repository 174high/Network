#include <linux/module.h>
#include <linux/string.h>
#include <linux/in.h>

static int __init client_init(void) 
{
	int sockfd;
	struct sockaddr_in ser_addr;
	int in_char , send_char;

	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sockfd < 0) {
		printk("sys_cmd_clt:Fail to create sock.\n");
		exit(1);
	}
	
	memset(&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	ser_addr.sin_port = htons(4000);
	
	printk("sys_cmd_clt:Send buf =>%s\n" , );
	
	send_char = sendto(sockfd,argv[1],strlen(argv[1]),0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	if (send_char != in_char) {
		printk("sys_cmd_clt:Fail!\n");
		close(sockfd);
		exit(1);
	}
	
	close(sockfd);

	return 0;
}

static void __exit client_exit(void)  
{  
	printk("%s:Exit..." , __func__);
}  	

module_init(client_init);  
module_exit(client_exit);   

MODULE_LICENSE("GPL");
