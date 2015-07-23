#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semun.h"

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

int main (int argc, char *argv[])
{
    int i;
    int pause_time;
    char op_char = 'O';
    srand((unsigned int)getpid());
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
    
    
}
