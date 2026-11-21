typedef struct {
    int n;
    sem_t s1;
    sem_t s2;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    sem_init(&obj->s1, 0, 0);
    sem_init(&obj->s2, 0, 1);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        
        sem_wait(&obj->s2);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        sem_post(&obj->s1);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->s1);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        sem_post(&obj->s2);
    }
}

void fooBarFree(FooBar* obj) {
    sem_destroy(&obj->s1);
    sem_destroy(&obj->s2);
    free(obj);
}