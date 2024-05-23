#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define N 10

int rc = 0; // Reader count
int buffer[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t db = PTHREAD_MUTEX_INITIALIZER;

void read_buffer() {
    printf("Reading Buffer\n");
}

void *reader(void *arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        rc++;
        if (rc == 1) { // First reader
            pthread_mutex_lock(&db);
        }
        pthread_mutex_unlock(&mutex);
        
        // Read from buffer
        read_buffer();
        
        pthread_mutex_lock(&mutex);
        rc--;
        if (rc == 0) { // Last reader
            pthread_mutex_unlock(&db);
        }
        pthread_mutex_unlock(&mutex);
        
        sleep(2); 
    }
}

void write_buffer() {
    printf("Writing to Buffer\n");
}

void *writer(void *arg) {
    while (true) {
        pthread_mutex_lock(&db);
        
        // Write to buffer
        write_buffer();
        
        pthread_mutex_unlock(&db);
        
        sleep(2);
    }
}

int main() {
    pthread_t reader_thread, writer_thread;
    pthread_create(&reader_thread, NULL, reader, NULL);
    pthread_create(&writer_thread, NULL, writer, NULL);

    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);
    return 0;
}