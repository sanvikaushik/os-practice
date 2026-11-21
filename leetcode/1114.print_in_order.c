#include <semaphore.h>  // sem_t, sem_init, sem_wait, sem_post, sem_destroy
#include <stdlib.h>     // malloc, free
typedef struct {
    // User defined data may be declared here.
    sem_t s1; 
    sem_t s2; 
    
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
        sem_init(&obj->s1, 0, 0);
    sem_init(&obj->s2, 0, 0);
    
    return obj;
}

void first(Foo* obj) {
    
    // printFirst() outputs "first". Do not change or remove this line.

    printFirst();
    sem_post(&obj->s1);
}

void second(Foo* obj) {
    
    // printSecond() outputs "second". Do not change or remove this line.
    sem_wait(&obj->s1);
    printSecond();
    sem_post(&obj->s2);
}

void third(Foo* obj) {
    
    // printThird() outputs "third". Do not change or remove this line.
    sem_wait(&obj->s2);
    printThird();
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    sem_destroy(&obj->s1);
    sem_destroy(&obj->s2);
    free(obj);
}