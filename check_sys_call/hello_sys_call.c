#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

#define __NR_sys_hello 388

int main()
{
	long int a = 45;
	a = syscall(__NR_sys_hello);
	printf("system call returned %ld\n",a);
	return 0;
}
