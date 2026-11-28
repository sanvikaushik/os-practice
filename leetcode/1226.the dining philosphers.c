#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t room;                  // At most 4 philosophers enter
    pthread_mutex_t forks[5];   // One mutex per fork
} DiningPhilosophers;

DiningPhilosophers* diningPhilosophersCreate() {
    DiningPhilosophers* obj = malloc(sizeof(DiningPhilosophers));

    // Allow at most 4 philosophers to attempt eating
    sem_init(&obj->room, 0, 4);

    // Initialize all 5 forks
    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&obj->forks[i], NULL);
    }

    return obj;
}

void wantsToEat(
    DiningPhilosophers* obj,
    int philosopher,
    void (*pickLeftFork)(),
    void (*pickRightFork)(),
    void (*eat)(),
    void (*putLeftFork)(),
    void (*putRightFork)()
) {
    int left = philosopher;
    int right = (philosopher + 1) % 5;

    // 1. Get permission to enter
    sem_wait(&obj->room);

    // 2. Acquire left fork
    pthread_mutex_lock(&obj->forks[left]);
    pickLeftFork();

    // 3. Acquire right fork
    pthread_mutex_lock(&obj->forks[right]);
    pickRightFork();

    // 4. Eat (both forks acquired)
    eat();

    // 5. Release right fork
    putRightFork();
    pthread_mutex_unlock(&obj->forks[right]);

    // 6. Release left fork
    putLeftFork();
    pthread_mutex_unlock(&obj->forks[left]);

    // 7. Leave the room
    sem_post(&obj->room);
}

void diningPhilosophersFree(DiningPhilosophers* obj) {
    sem_destroy(&obj->room);

    for (int i = 0; i < 5; i++) {
        pthread_mutex_destroy(&obj->forks[i]);
    }

    free(obj);
}