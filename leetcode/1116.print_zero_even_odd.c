typedef struct {
    int n;
    sem_t semZero;
    sem_t semEven;
    sem_t semOdd;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    sem_init(&obj->semZero, 0, 1);
    sem_init(&obj->semOdd, 0, 0);
    sem_init(&obj->semEven, 0, 0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void printNumber(int x);

void zero(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i++) {
        sem_wait(&obj->semZero);
        printNumber(0);

        if (i % 2 == 1) {
            sem_post(&obj->semOdd);
        }

        else {
            sem_post(&obj->semEven);
        }
    }

}

void even(ZeroEvenOdd* obj) {
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->semEven);
        printNumber(i);
        sem_post(&obj->semZero);
    }
}

void odd(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->semOdd);
        printNumber(i);
        sem_post(&obj->semZero);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    sem_destroy(&obj->semZero);
    sem_destroy(&obj->semOdd);
    sem_destroy(&obj->semEven);
    free(obj);
}