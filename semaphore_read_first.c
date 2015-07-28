#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

union semun 
{
    int val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

int main ()
{
    int i;
    int pause_time;
    int status;
    char op_char = 'O';
    srand((unsigned int)getpid());
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
    
    if (!set_semvalue()) 
    {
        fprintf(stderr, "Failed to initialize semaphore\n");
        exit(EXIT_FAILURE);
    }
    //op_char = 'X';
    //sleep(2);
    
    char *argc[] = {"./printer","Process_Read_first",NULL};
    for(i = 0; i < 10; i++) 
    {
        if (!semaphore_p())     
            exit(EXIT_FAILURE);
        pid_t pid = fork();
        if(pid == (pid_t)0)
        {
            execv("./printer",argc);
        }
        //fflush(stdout);
        //pause_time = rand() % 3;
        sleep(1);
        //printf("%c", op_char);
        //fflush(stdout);
        pid_t pid_second = fork();
        if(pid_second == (pid_t)0)
        {
            execv("./printer",argc);
        }
        int ret_child = waitpid(pid,&status,0);
        int ret_s_child = waitpid(pid_second,&status,0);
        printf("Rading here first\n");
        fflush(stdout);
        if (!semaphore_v()) 
            exit(EXIT_FAILURE);
        pause_time = rand() % 2;
        sleep(pause_time);
    }
    
    printf("\n%d - finished\n", getpid());
    //if (argc > 1) 
    //{
        sleep(4);
        del_semvalue();
    //}
    exit(EXIT_SUCCESS);
}

static int set_semvalue(void)
{
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) 
        return(0);
    return(1);
}

static void del_semvalue(void)
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p(void)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; /* P() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) 
    {
        fprintf(stderr, "semaphore_p failed\n");
        return(0);
    }
    return(1);
}

static int semaphore_v(void)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) 
    {
        fprintf(stderr, "semaphore_v failed\n");
        return(0);
    }
    return(1);
}
