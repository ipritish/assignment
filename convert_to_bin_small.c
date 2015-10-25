#include<stdio.h>

unsigned int int_to_int(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_int(k / 2)));
}

int main()
{
	unsigned int a = 388;
	printf("result is %u\n",int_to_int(a));
	return 0;
}
