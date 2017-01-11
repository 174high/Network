#Network---socket application

#ker_clt.c 			kernel中的socket客服端，未完成
#sys_cmd.c 			Android中BT on/off测试

#sys_cmd_clt.c  	UDP客户端模型，userspace
#sys_cmd_ser.c 		UDP服务端模型，userspace

#user_service_nl.c 	userspace中的服务端，采用netlink
socket编程，用于接收来自Android kernel中的消息
#kernel_client_nl.c kerbel中的socket客户端，采用netlink
socket编程，用于向Android userspace发送消息
		
