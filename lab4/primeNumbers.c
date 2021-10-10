// To compile: $ gcc primeNumber.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 100


void *checkPrime(void *vargp) {
    int *num = (int *)vargp;
    int i, flag = 0;

    for (i = 2; i <= (*num) / 2; ++i) {
        if ((*num) % i == 0) {
            flag = 1;
            break;
        }
    }

    if ((*num) == 1) {
        // printf("Neither prime nor composite: 1\n");
    } 
    else {
        if (flag == 0)
        printf("PRIME:     %d\n", *num);
        // else
        // printf("NOT PRIME: %d\n", *num);
    }   
    pthread_exit(NULL);
}
   
int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    for (int i = 1; i <= 100; i++) {
        rc = pthread_create(&threads[i-1], NULL, checkPrime, (void *)&i);
        pthread_join(threads[i-1], NULL);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}