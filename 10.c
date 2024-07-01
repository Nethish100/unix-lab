#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

int shared_resource = 0; // Shared resource
sem_t semaphore; // Semaphore declaration

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    sem_wait(&semaphore); // Wait for semaphore
    printf("Thread %d accessing shared resource.\n", thread_id);
    shared_resource++;
    printf("Shared resource value incremented to: %d\n", shared_resource);
    sem_post(&semaphore); // Release semaphore
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    sem_init(&semaphore, 0, 1); // Initialize semaphore

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]); // Create threads
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Join threads
    }

    sem_destroy(&semaphore); // Destroy semaphore

    return 0;
}
