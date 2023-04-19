#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16
#define NUM_INCREMENTS 10000

pthread_mutex_t lock;
int count = 0;

void *thread(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int rc;

    rc = pthread_mutex_init(&lock, NULL);
    if (rc) {
        fprintf(stderr, "Error initializing mutex: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, thread, NULL);
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

    rc = pthread_mutex_destroy(&lock);
    if (rc) {
        fprintf(stderr, "Error destroying mutex: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    printf("Expected result: %d, actual result: %d\n", NUM_THREADS * NUM_INCREMENTS, count);

    return 0;
}