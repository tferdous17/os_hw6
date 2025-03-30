#include <stdio.h>
#include <pthread.h>

int sharedData = 0;
pthread_mutex_t mutex;

void* writerThread(void* arg) {
    pthread_mutex_lock(&mutex);
    sharedData = 10;
    printf("Writer: Wrote %d\n", sharedData);
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

void* readerThread(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Reader: Read value %d\n", sharedData);
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

int main(void) {
    pthread_t thread1, thread2;

    // initialize mutex
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        return 1;
    }

    // create threads
    if (pthread_create(&thread1, nullptr, writerThread, nullptr) != 0) {
        return 1;
    }
    if (pthread_create(&thread2, nullptr, readerThread, nullptr) != 0) { 
        return 1;
    }

    // wait for threads to complete
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    // cleanup stuff
    pthread_mutex_destroy(&mutex);
    printf("Program completed\n");

    return 0;
}