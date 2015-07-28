#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("Passed value is %s\n",argv[1]);
    }
//    printf("Integer is %d\n",argc);
    fflush(stdout);

    return 0;

}
