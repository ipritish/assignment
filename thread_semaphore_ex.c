#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function_a(void *arg);
void *thread_function_b(void *arg);
void *thread_function_c(void *arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main() 
{
    int res,res_one,res_two,res_three;
    pthread_t a_thread;
    pthread_t b_thread;
    pthread_t c_thread;
    void *thread_result_a;
    void *thread_result_b;
    void *thread_result_c;
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0) 
    {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    res_one = pthread_create(&a_thread, NULL, thread_function_a, NULL);
    res_two = pthread_create(&b_thread,NULL,thread_function_b,NULL);
    res_three = pthread_create(&c_thread,NULL,thread_function_c,NULL);
    if (res_one != 0 || res_two != 0 || res_three != 0) 
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Input some text. Enter 'end' to finish\n");
    while(strncmp("end", work_area, 3) != 0) 
    {
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(&bin_sem);
        sem_post(&bin_sem);
        sem_post(&bin_sem);
    }
    printf("\nWaiting for thread to finish...\n");
    res_one = pthread_join(a_thread, &thread_result_a);
    res_two = pthread_join(b_thread,&thread_result_b);
    res_three = pthread_join(c_thread,&thread_result_c);
    
    if (res_one != 0 || res_two != 0 || res_three != 0) 
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}

void *thread_function_a(void *arg) 
{
    sem_wait(&bin_sem);
    while(strncmp("end", work_area, 3) != 0) 
    {
        printf("You input %d characters\n", strlen(work_area) -1);
        sleep(1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

void *thread_function_b(void *arg)
{
    sem_wait(&bin_sem);
    while(strncmp("end", work_area, 3) != 0)
    {
        printf("Your first char %c : \n", work_area[0]);
        sleep(1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

void *thread_function_c(void *arg)
{
    sem_wait(&bin_sem);
    while(strncmp("end", work_area, 3) != 0)
    {
        printf("You input contain %c character\n", work_area[0]);
        sleep(1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}
