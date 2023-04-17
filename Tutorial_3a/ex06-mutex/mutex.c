/*
 * mutex.c
 *
 *  Created on: Mar 19, 2016
 *      Author: jiaziyi
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 50
void *increase_counter(void *);
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int  counter = 0;

int main()
{

	//create 50 threads of increase_counter, each thread adding 1 to the counter
	pthread_t thread_a[NTHREADS];
	for(int i = 0; i <NTHREADS; i++){
		if(pthread_create(&thread_a[i], NULL, increase_counter, NULL)) {
        	fprintf(stderr, "Error creating thread\n");
        	return 1;
    	}
	}

	for (int i = 0; i < NTHREADS; i++)
        pthread_join(thread_a[i], NULL);

	printf("\nFinal counter value: %d\n", counter);
	pthread_mutex_destroy(&lock);
}

void *increase_counter(void *arg)
{

	printf("Thread number %ld, working on counter. The current value is %d\n", (long)pthread_self(), counter);
	pthread_mutex_lock(&lock);
	int i = counter;
	usleep (10000); //simulate the data processing
	counter = i+1;
	pthread_mutex_unlock(&lock);

}
