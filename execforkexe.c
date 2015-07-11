#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>

int main (int argc, char *argv[])
{
    char *my_env[] = {"FOOD=coffee",NULL};
    int status;
    int anotherstatus;
    int psstatus;
    pid_t ps_pid = fork();
        if (ps_pid == 0)
        {
            execl("/bin/ps","ps",NULL);
            printf("exec error");
        }

    pid_t pid = fork();
    if (pid == 0)
    {
        //this is child
        fprintf(stderr,"In child one\n");
        if(execle("./coffee","./coffee","donut",NULL,my_env) == -1)
        {
            fprintf(stderr,"Can't run process 0: %s\n",strerror(errno));
            return 1;
        }
    
    }
    if (pid > 0)
    {
        
        pid_t child_two_pid = vfork();
        if (child_two_pid == 0)
        {
            fprintf(stderr,"in child two\n");
            char *parmList[] = {"./coffee","coffee","donut",NULL};
            execv("./coffee", parmList);
            printf("Return not expected. Must be an execv error.n");
        }
        //this is parent
        
        pid_t child_status = waitpid(child_two_pid,&status,0);
        pid_t child_one_status = waitpid(pid,&anotherstatus,0);
        pid_t ps_pid_status = waitpid(ps_pid,&psstatus,0);
        if (child_status == -1)
            perror("wait");
        if (WIFEXITED (status))
             printf ("Normal termination with exit status=%d and errorno%s\n", WEXITSTATUS (status),strerror(errno));

        if (WIFSIGNALED (status))
             printf ("Killed by signal=%d%s\n", WTERMSIG (status), WCOREDUMP (status) ? " (dumped core)" : "");

        if (WIFSTOPPED (status))
            printf ("Stopped by signal=%d\n", WSTOPSIG (status));

        if (WIFCONTINUED (status))
            printf ("Continued\n");
    }
    return 0;
}
