#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t semA;
    sem_t semB;
} Alternator;

void *printA(void *arg) {
    Alternator *obj = (Alternator *)arg;

    for (int i = 0; i < obj->n; i++) {

        // BLANK 1: Wait for permission to print A
        sem_wait(&obj->semA);

        printf("A");
        
        // BLANK 2: Give B permission
        sem_post(&obj->semA);
        
    }

    return NULL;
}

void *printB(void *arg) {
    Alternator *obj = (Alternator *)arg;

    for (int i = 0; i < obj->n; i++) {

        // BLANK 3: Wait for permission to print B
        sem_wait(&obj->semB);

        printf("B");
        // BLANK 4: Give A permission
        sem_post(&obj->semA);

    }

    return NULL;
}

int main(void) {
    Alternator obj;
    obj.n = 3;

    // BLANK 5: Initialize semA
    sem_init(&obj->semA, 0, 0);
    // BLANK 6: Initialize semB
    sem_init(&obj->semB, 0, 1);

    pthread_t a, b;

    // Deliberately create A first!
    pthread_create(&a, NULL, printA, &obj);
    pthread_create(&b, NULL, printB, &obj);

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    sem_destroy(&obj.semA);
    sem_destroy(&obj.semB);

    printf("\n");
    return 0;
}