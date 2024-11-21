#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

int reader_count = 0;
int data = 0;
pthread_mutex_t readerx;
sem_t writery;

void *reader(void *arg) {
    int num = (intptr_t)arg;
    int i = 5;
    while (i--) {
        pthread_mutex_lock(&readerx);
        reader_count++;
        if (reader_count == 1)
            sem_wait(&writery);
        pthread_mutex_unlock(&readerx);

        printf("%d reader reading the data %d\n", num, data);

        pthread_mutex_lock(&readerx);
        reader_count--;
        if (reader_count == 0)
            sem_post(&writery);
        pthread_mutex_unlock(&readerx);

        sleep(rand() % 10 + 1);
    }
    return NULL;
}

void *writer(void *arg) {
    int num = (intptr_t)arg;
    int i = 2;
    while (i--) {
        sem_wait(&writery);

        data += 5;
        printf("%d writer update data to %d\n", num, data);

        sem_post(&writery);
        sleep(rand() % 10 + 1);
    }
    return NULL;
}

int main() {
    pthread_t Treader[5], Twriter[5];

    pthread_mutex_init(&readerx, NULL);
    sem_init(&writery, 0, 1);

    // srand(time(NULL)); // Initialize random seed

    for (int i = 0; i < 5; i++) {
        pthread_create(&Treader[i], NULL, reader, (void *)(intptr_t)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&Twriter[i], NULL, writer, (void *)(intptr_t)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(Treader[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(Twriter[i], NULL);
    }

    pthread_mutex_destroy(&readerx);
    sem_destroy(&writery);

    return 0;
}
