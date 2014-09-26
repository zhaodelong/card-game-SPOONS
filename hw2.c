// hw 3
// Delong Zhao
// 113800046

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
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex_x;
int spoons = 3;

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
	{
		cout << arg[n] << ' ';
	}
  	cout << '\n';
}

// thread function
void *client(void *threadid)
{
	int tid;
	tid = (int)threadid;

while (spoons >=0){
		
	pthread_mutex_lock(&mutex_x);

	
	if (tid == 0) {	
		if (!b0Que.empty()){	
				
				if (spoons < 3) {
					printf("P%d win #: %d \n", tid, (4-spoons));
					printf("P%d, final cards are:\n", tid);
					fflush(stdout);
					printarray(p0_cards,5);			
					spoons--;
					break;
							
				} else if (spoons == 3){		
					printf("P%d, old cards are:\n", tid);
					printarray(p0_cards,5);
					int i = 0;
					int tmp;
			
					tmp = b0Que.front();
					b0Que.pop();
		
					for(i=0; i < 5; i++ )
					{
						if((p0_cards[i]) %4 != 0)
						{
							b1Que.push(p0_cards[i]);
							printf("P%d discard: %d \n", tid, p0_cards[i]);
							p0_cards[i] = tmp;
							printf("P%d pick up: %d \n", tid, p0_cards[i]);
							break;
						}
					}
		
					printf("P%d, new cards are:\n", tid);			
					printarray(p0_cards,5);
		
					if ((p0_cards[4]%4 == 0)&&(p0_cards[0]%4 == 0)&&(p0_cards[1]%4 == 0)&&(p0_cards[2]%4 == 0)&&(p0_cards[3]%4 == 0))
					{
						printf("P%d win #: %d \n", tid, (4-spoons));
						printf("P%d, final cards are:\n", tid);
						printarray(p0_cards,5);	
						spoons--;
						break;			
					}
			
				}
			
		}	
	}else if (tid == 1) {
		if (!b1Que.empty()){
			
				if (spoons < 3) {
					printf("P%d win #: %d \n", tid, (4-spoons));
					printf("P%d, final cards are:\n", tid);
					fflush(stdout);
					printarray(p1_cards,5);			
					spoons--;
					break;
							
				} else if (spoons == 3){		
					printf("P%d, old cards are:\n", tid);
					printarray(p1_cards,5);
					int i = 0;
					int tmp;
			
					tmp = b1Que.front();
					b1Que.pop();
		
					for(i=0; i < 5; i++ )
					{
						if((p1_cards[i]) %4 != 1)
						{
							b2Que.push(p1_cards[i]);
							printf("P%d discard: %d \n", tid, p1_cards[i]);
							p1_cards[i] = tmp;
							printf("P%d pick up: %d \n", tid, p1_cards[i]);
							break;
						}
					}
		
					printf("P%d, new cards are:\n", tid);			
					printarray(p1_cards,5);
		
					if ((p1_cards[4]%4 == 1)&&(p1_cards[0]%4 == 1)&&(p1_cards[1]%4 == 1)&&(p1_cards[2]%4 == 1)&&(p0_cards[3]%4 == 1))
					{
						printf("P%d win #: %d \n", tid, (4-spoons));
						printf("P%d, final cards are:\n", tid);
						printarray(p1_cards,5);	
						spoons--;
						break;			
					}			
			
				}
		
			
		}
	}else if (tid == 2) {
		if (!b2Que.empty()){
			
				if (spoons < 3) {
					printf("P%d win #: %d \n", tid, (4-spoons));
					printf("P%d, final cards are:\n", tid);
					fflush(stdout);
					printarray(p2_cards,5);			
					spoons--;
					break;
						
				} else  if (spoons == 3){		
					printf("P%d, old cards are:\n", tid);
					printarray(p2_cards,5);
					int i = 0;
					int tmp;
			
					tmp = b2Que.front();
					b2Que.pop();
		
					for(i=0; i < 5; i++ )
					{
						if((p2_cards[i]) %4 != 2)
						{
							b3Que.push(p2_cards[i]);
							printf("P%d discard: %d \n", tid, p2_cards[i]);
							p2_cards[i] = tmp;
							printf("P%d pick up: %d \n", tid, p2_cards[i]);
							break;
						}
					}
	
					printf("P%d, new cards are:\n", tid);			
					printarray(p2_cards,5);
	
					if ((p2_cards[4]%4 == 2)&&(p2_cards[0]%4 == 2)&&(p2_cards[1]%4 == 2)&&(p2_cards[2]%4 == 2)&&(p2_cards[3]%4 == 2))
					{
						printf("P%d win #: %d \n", tid, (4-spoons));
						printf("P%d, final cards are:\n", tid);
						printarray(p2_cards,5);	
						spoons--;
						break;			
					}
			
				}
			
			
		}
	}else if (tid == 3) {
		if (!b3Que.empty()){
			
				if (spoons < 3 ) {
					printf("P%d win #: %d \n", tid, (4-spoons));
					printf("P%d, final cards are:\n", tid);
					fflush(stdout);
					printarray(p3_cards,5);			
					spoons--;
					break;
							
				} else  if (spoons == 3) {		
					printf("P%d, old cards are:\n", tid);
					printarray(p3_cards,5);
					int i = 0;
					int tmp;
			
					tmp = b3Que.front();
					b3Que.pop();
		
					for(i=0; i < 5; i++ )
					{
						if((p3_cards[i]) %4 != 3)
						{
							b0Que.push(p3_cards[i]);
							printf("P%d discard: %d \n", tid, p3_cards[i]);
							p3_cards[i] = tmp;
							printf("P%d pick up: %d \n", tid, p3_cards[i]);
							break;
						}
					}
		
					printf("P%d, new cards are:\n", tid);			
					printarray(p3_cards,5);
		
					if ((p3_cards[4]%4 == 3)&&(p3_cards[0]%4 == 3)&&(p3_cards[1]%4 == 3)&&(p3_cards[2]%4 == 3)&&(p3_cards[3]%4 == 3))
					{
						printf("P%d win #: %d \n", tid, (4-spoons));
						printf("P%d, final cards are:\n", tid);
						printarray(p3_cards,5);	
						spoons--;
						break;			
					}			
				}
			
		}
	}
	pthread_mutex_unlock(&mutex_x);
	cout << spoons << " tid:" << tid <<  endl;
	
	
}


if (spoons < 3){
	pthread_mutex_unlock(&mutex_x);	
	cout << "loser" << endl;
}	
	pthread_exit((void*) 0);
		
}

int main (int argc, char *argv[])
{
	
	int i,j;
	
	for (i = 0; i < 52; i++)
	{
		cards[i] = i;
	}	

	shuffle(cards, 52); // shuffle cards

	// give 5 cards to each player
	for (j = 0; j < 5; j++ ) p0_cards[j] = cards[j];
	for (j = 5; j < 10; j++ ) p1_cards[j-5] = cards[j];
	for (j = 10; j < 15; j++ ) p2_cards[j-10] = cards[j];
	for (j = 15; j < 20; j++ ) p3_cards[j-15] = cards[j];
	
	
	
	//give 8 cards to buffer between each 2 players. 4 buffers total.
	
	for (j = 0; j < 8; j++)
	{
		b0Que.push(cards[20+j]);
		b1Que.push(cards[28+j]);
		b2Que.push(cards[36+j]);
		b3Que.push(cards[44+j]);
	}		
	
	//start playing
	void *status;
	pthread_mutex_init(&mutex_x, NULL);
	
	
	for(i=0;i<NUM_THREADS;i++)
  	{  	
   		pthread_create(&threads[i], NULL, client, (void *)i); 
   	}	
	
	/* Wait on the other threads */

	for(i=0;i<NUM_THREADS;i++) {
  		pthread_join(threads[i], &status);
  	}
	/* After joining, print out the results and cleanup */
	pthread_mutex_destroy(&mutex_x);
	pthread_exit(NULL);

}   


