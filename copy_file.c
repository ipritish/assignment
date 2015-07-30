#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc , char *argv[])
{
    char c;
    int in, out;
    if (argc > 1)
    {
        in = open(argv[1], O_RDONLY);
        out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
        while(read(in,&c,1) == 1)
            write(out,&c,1);
    }
    else
    {
        printf("No arguement given");
        exit(1);
    }
    exit(0);
}
