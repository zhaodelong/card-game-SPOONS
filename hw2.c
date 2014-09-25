#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;

/* Define globally accessible variables and a mutex */
#define NUM_THREADS	4
int cards[52]; //52 cards
int p0_cards[5], p1_cards[5], p2_cards[5], p3_cards[5];	// 5 cards per player.
queue <int> b0Que, b1Que, b2Que, b3Que; // 4 buffers between each two players.
pthread_t callThd[NUM_THREADS];
pthread_mutex_t mutexsum;

/* Shuffle cards function */
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

//print elements of a given array
void printarray (int arg[], int length) {
  for (int n=0; n<length; ++n)
    cout << arg[n] << ' ';
  cout << '\n';
}

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   printarray(cards,52);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	
	int i,j;
	for (i = 0; i < 52; i++)
	{
		cards[i] = i;
	}

	printarray(cards,52);

	//shuffle(cards, 52); // shuffle cards

	printarray(cards,52);

	
	for (j = 0; j < 5; j++ ) p0_cards[j] = cards[j];
	for (j = 5; j < 10; j++ ) p1_cards[j-5] = cards[j];
	for (j = 10; j < 15; j++ ) p2_cards[j-10] = cards[j];
	for (j = 15; j < 20; j++ ) p3_cards[j-15] = cards[j];
	
	printarray(p0_cards,5);
	printarray(p1_cards,5);
	printarray(p2_cards,5);
	printarray(p3_cards,5);	
	
	//give 8 cards to buffer between each 2 players. 4 buffers total.
	
	for (j = 0; j < 8; j++)
	{
		b0Que.push(cards[20+j]);
		b1Que.push(cards[28+j]);
		b2Que.push(cards[36+j]);
		b3Que.push(cards[44+j]);
	}	
		
	// cout << "Size :" << b3Que.size() << endl;
	
	/*
	while(!b3Que.empty())
	{
		cout << ""<< b3Que.front()<< endl;
		b3Que.pop();
	}
	cout << b3Que.size() << endl;
	*/	
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	   for(t=0;t<NUM_THREADS;t++){
	     printf("In main: creating thread %ld\n", t);
	     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
	     if (rc){
	       printf("ERROR; return code from pthread_create() is %d\n", rc);
	       exit(-1);
	       }
	     }

	   /* Last thing that main() should do */
	   pthread_exit(NULL);


}   


