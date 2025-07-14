#include <stdio.h>
#include <pthread.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    int rc = pthread_mutex_lock(&mutex);
    assert(rc == 0);
    balance++;
    rc = pthread_mutex_unlock(&mutex);
    assert(rc == 0);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    int rc = pthread_mutex_lock(&mutex);
    assert(rc == 0);
    balance++; // unprotected access
    rc = pthread_mutex_unlock(&mutex);
    assert(rc == 0);
    Pthread_join(p, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
