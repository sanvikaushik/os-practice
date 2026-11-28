#include <stdio.h>
#include <pthread.h>

void *worker(void *arg) {
    (void)arg;
    printf("Hello from worker!\n");
    return NULL;
}

int main(void) {
    pthread_t t;

    pthread_create(&t, NULL, worker, NULL);
    pthread_join(t, NULL);
    
    printf("Main finished!\n");
    return 0;
}