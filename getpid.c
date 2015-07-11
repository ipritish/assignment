#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
//pid_t getpid (void);
int main()
{
int pid;
printf("My pid=%d\n", getpid ());
printf("Parent's pid=%d\n", getppid ());
pid = fork();
if(pid==0) {
    printf("I am the Child process and my pid=%d\n",getpid());
    execl ("/bin/ls","ls",NULL);
    }
else if (pid>0)
    {
    printf("I am the Parent and my pid =%d childpid=%d\n",getpid(),pid);
    sleep(1000);
    }
else if (pid == -1)
    printf("Error in fork syscall\n");
}
