#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS	5
int x = 0;
pthread_mutex_t mutex_x;
pthread_t threads[NUM_THREADS];

void *client(void *threadid)
{
	int tid;
   	tid = (int)threadid;
	pthread_mutex_lock(&mutex_x);
	
	fprintf(stdout, "TID %d: mutex_lock \n", tid);
	x++;
	fprintf(stdout, "TID %d:mutex modifying x value: %d \n", tid, x);
	pthread_mutex_unlock(&mutex_x);
	fprintf(stdout, "TID %d: mutex_unlock\n",tid);
	pthread_exit((void*) 0);
}

int main(void){
	int i;
	void *status;

	//pthread_attr_t attr;

	pthread_mutex_init(&mutex_x, NULL);
	
	//pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	
   	long t;
   	for(i=0;i<NUM_THREADS;i++)
  	{
  	/* Each thread works on a different set of data.
   	* The offset is specified by 'i'. The size of
   	* the data for each thread is indicated by VECLEN.
   	*/
   	pthread_create(&threads[i], NULL, client, (void *)i); 
   	}	

	// pthread_attr_destroy(&attr);
	/* Wait on the other threads */

	for(i=0;i<NUM_THREADS;i++) {
  		pthread_join(threads[i], &status);
  	}
	/* After joining, print out the results and cleanup */

	printf ("x =  %d \n", x);
	pthread_mutex_destroy(&mutex_x);
	pthread_exit(NULL);
	
}
