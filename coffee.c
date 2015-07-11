#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    char *w = getenv("EXTRA");
    int val = nice(0);
    int ret;
    if (!w)
        w = getenv("FOOD");
    if (!w)
        w = argv[argc - 1];
    char *c = getenv("EXTRA");
    if(!c)
        c = argv[argc - 1];
    printf("%s with %s\n",c,w);
    //while(1);
    /* we want a nice value of 10 */
    val = 10 - val;
    errno = 0;
    printf("\nprevious nice value %d\n",val);
    ret = nice (val);
    printf("New nice value %d\n",ret);
    if (ret == -1 && errno != 0)
        perror ("nice");
    else
        printf ("nice value is now %d\n", ret);
    sleep(10);
    return 0;
}
