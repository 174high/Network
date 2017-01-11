#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int ret = 0;
	
	printf("%s:sys_cmd start!\n" , __func__);	
	//ret = system("service call bluetooth_manager 8");
	ret = system("service call bluetooth_manager 8 > /data/harrytest11.txt");
	ret = system("sleep 3");
	ret = system("service call bluetooth_manager 6 >> /data/harrytest11.txt");
	printf("%s:ret=%d\n" , __func__ , ret);	
	
	return 0;
}
