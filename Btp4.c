#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


pthread_mutex_t MeuMutex;

void terminal_clear() {
    printf("\033[2J"); fflush(stdout);
}

void terminal_print_at(int line, const char *st) {
    printf("\033[%d;%dH", line, 1); fflush(stdout);
    puts(st); fflush(stdout);
}

void* printer(void *arg) {
    
	//Pick a pseudo-random line [1..10]
	int line = (long)pthread_self()%10 + 1;

    while(1) {       
        pthread_mutex_lock(&MeuMutex);
        terminal_print_at(line, arg);
        pthread_mutex_unlock(&MeuMutex);
		usleep(100*1000); //100 ms
    }

    return NULL;
}



int main(void)
{
    /*pthread_mutex_init()
    pthread_mutex_lock()
    pthread_mutex_unlock()
    pthread_mutex_destroy()*/
    pthread_mutexattr_t   mta;
    int rc = pthread_mutexattr_init(&mta);

    if(pthread_mutex_init(&MeuMutex, NULL)){
        printf("Mutex can't be created.\nERROR\n");
        return -1;
    }
    else printf("Mutex created w sucess!\n");

    pthread_mutex_lock(&MeuMutex);
    pthread_mutex_unlock(&MeuMutex);
    pthread_t tid[3];

    terminal_clear();


	pthread_create(&(tid[0]), NULL, &printer, "I'm a very long long long long long long long long long long long long long long string");
    pthread_create(&(tid[1]), NULL, &printer, "short string 1");
    pthread_create(&(tid[2]), NULL, &printer, "short string 2");

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    return 0;
}