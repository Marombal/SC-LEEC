#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "p5_helper.h"

#define BUFFER_MAX_SIZE 4

pthread_mutex_t MeuMutex;

unsigned int data_space[BUFFER_MAX_SIZE];
circ_buff_t buffer = { 
    data_space,
    BUFFER_MAX_SIZE,
    0,
    0
};

void* producer(void *arg)
{
    unsigned int push_value;
    while (1) {
        push_value = (rand() % 1000); //random [0,999]
        pthread_mutex_lock(&MeuMutex);
        if (circ_buff_push(&buffer, push_value ) == 0)
            printf("Producer: %u\n", push_value);
        else
            printf("Producer: buffer is full\n"); 
        pthread_mutex_unlock(&MeuMutex);
        usleep(100*1000); //100 ms
    }
    
    return NULL;
}

void* consumer(void *arg)
{
    unsigned int pop_value;
    while (1) {
        pthread_mutex_lock(&MeuMutex);
        if (circ_buff_pop(&buffer, &pop_value)==0)
            printf("                              Consumer: returned %u\n", pop_value);
        else
            printf("                              Consumer: buffer is empty\n");
        pthread_mutex_unlock(&MeuMutex);
        usleep(150*1000); //150 ms
    }
    
    return NULL;
}
int main(void)
{
    //Seeding...
	srand(time(NULL));

    pthread_mutexattr_t mta;
    int rc = pthread_mutexattr_init(&mta);

    //pthread_mutex_lock(&MeuMutex);
    //pthread_mutex_unlock(&MeuMutex);

    if(pthread_mutex_init(&MeuMutex, NULL)){
        printf("Mutex can't be created.\nERROR\n");
        return -1;
    }
    else printf("Mutex created w sucess!\n");

    pthread_t tid[2];
    
	pthread_create(&(tid[0]), NULL, &producer, NULL);
	pthread_create(&(tid[1]), NULL, &consumer, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}