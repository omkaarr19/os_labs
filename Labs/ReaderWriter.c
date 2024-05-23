#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, writeBlock; 
int data = 0, readersCount = 0;

void *reader(void *arg) {
    int readerId = *(int*)arg;
    while (1) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {   
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);

        printf("Reader %d reads data: %d\n", readerId, data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    int writerId = *(int*)arg;
    while (1) {
        sem_wait(&writeBlock);
        
        data++;
        printf("Writer %d writes data: %d\n", writerId, data);

        sem_post(&writeBlock);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
