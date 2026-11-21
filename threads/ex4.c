#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *threadA(void *arg) {
    (void)arg;

    printf("Hello\n");
    sem_post(&s);

    return NULL;
}

void *threadB(void *arg) {
    (void)arg;

    sem_wait(&s);
    printf("World\n");

    return NULL;
}

int main(void) {
    pthread_t a, b;

    sem_init(&s, 0, 0);  // Initialize GLOBAL semaphore

    pthread_create(&b, NULL, threadB, NULL);
    pthread_create(&a, NULL, threadA, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    sem_destroy(&s);
    return 0;
}