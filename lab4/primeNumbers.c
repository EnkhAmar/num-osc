
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5
  
// Let us create a global variable to change it in threads
int g = 0;
  
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
  
    // Let us create a static variable to observe its changes
    static int s = 0;
  
    // Change static and global variables
    ++s; ++g;
  
    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

void *checkPrime(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello world! Thread Id, %d", tid);
    pthread_exit(NULL);
}
  
int main()
{
    pthread_t threads[NUM_THREADS];
    int rc, i;
    for (i = 0; i < NUM_THREADS; i++) {
        printf("main() : creating thread, %d\n", i);
        rc = pthread_create(&threads[i], NULL, checkPrime, (void *)i);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }
  
    pthread_exit(NULL);
    return 0;
}