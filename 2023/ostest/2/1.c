#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16
#define NUM_INCREMENTS 10000

void *thread(void *arg) {
    int *count = (int *) arg;
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        (*count)++;
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int count = 0;
    int rc;

    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, thread, (void *) &count);
        if (rc) {
            fprintf(stderr, "Error creating thread: %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            fprintf(stderr, "Error joining thread: %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    printf("Expected result: %d, actual result: %d\n", NUM_THREADS * NUM_INCREMENTS, count);

    return 0;
}