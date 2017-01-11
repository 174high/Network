#include <net/sock.h>
#include <net/netlink.h>
#include <linux/skbuff.h>
#include <linux/string.h>
#include <linux/module.h>

#define MY_GROUP    1

struct sock* socket;
struct sk_buff* socket_buff;

static void nl_receive_callback (struct sk_buff *skb)                                                     
{                                                                                                     
	pr_err("%s:Enter!\n" , __func__);
	nlmsg_free(skb);

	return ;
}                                                                                                     

static void kernel_send_nl_msg(void)                                                                  
{                                                                                                     
	struct nlmsghdr *nlsk_mh;                                                                         
	char* msg = "hello kernel";

	struct netlink_kernel_cfg cfg = {
		.input  = nl_receive_callback,
	};


	pr_err("%s:Enter!\n" , __func__);

	socket = netlink_kernel_create(&init_net, NETLINK_USERSOCK, &cfg);
	if (!socket) {                                                                                                                                                             
		pr_err("%s:Failed to create netlink socket\n" , __func__);
		return -ENOMEM;
	}

	socket_buff = nlmsg_new(256, GFP_KERNEL);                                                                                                                                                                                                                                                 
	nlsk_mh = nlmsg_put(socket_buff, 0, 0, NLMSG_DONE, strlen(msg), 0);                       
//	NETLINK_CB(socket_buff).pid = 0;    // kernel pid                                                   
	NETLINK_CB(socket_buff).dst_group = MY_GROUP;                                                     
	strcpy(nlmsg_data(nlsk_mh), msg);                                                                

	nlmsg_multicast(socket, socket_buff, 0, MY_GROUP, GFP_KERNEL);                    

	return ;                                                                                           
}

static int __init client_init(void) 
{
	pr_err("%s:Init!\n" , __func__);

	kernel_send_nl_msg();
	return 0;
}

static void __exit client_exit(void)
{
	pr_err("%s:Exit!\n" , __func__);

}

module_init(client_init);  
module_exit(client_exit);   

MODULE_LICENSE("GPL");
