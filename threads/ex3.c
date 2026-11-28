#include <pthread.h>
#include <stdio.h>

void *worker(void *arg) {
    (void)arg;
    printf("B\n");
    return NULL;
}

int main(void) {
    pthread_t t;

    printf("A\n"); // A will always print first

    // any order -> BC or CB
    pthread_create(&t, NULL, worker, NULL);
    printf("C\n");

    pthread_join(t, NULL);

    // After join -> Always D at end
    printf("D\n");

    return 0;
}