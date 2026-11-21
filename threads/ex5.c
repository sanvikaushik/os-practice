#include <stdio.h>
#include <pthread.h>

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    (void)arg;
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%d\n", counter);
    return 0;
}