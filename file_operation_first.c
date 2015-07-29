#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>

int main ()
{
    int fd;
    fd = open("./reader.txt",O_RDWR | O_CREAT | O_EXCL , 0777);
    exit(0);
}
