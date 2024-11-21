#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define R 5  // Number of readers
#define W 5  // Number of writers

int readcount;  // Counter for active readers

sem_t wsem;  // Semaphore for controlling writer access
pthread_mutex_t x;  // Mutex for controlling readcount and ensuring thread safety
int s = 5;  // Shared resource (initial value 5)

void *reader1(void *a);  // Reader thread function declaration
void *writer1(void *a);  // Writer thread function declaration

int main() {
    int i, op;
    pthread_t thread_reader[R], thread_write[W];
    
    pthread_mutex_init(&x, NULL);  // Initialize the mutex
    sem_init(&wsem, 0, 1);         // Initialize semaphore for write access

    do {
        printf("Menu: 1. Reader have priority \n 2. Exit");
        scanf("%d", &op);

        switch(op) {
            case 1:
                readcount = 0;
                for(i = 0; i < W; i++) {
                    pthread_create(&thread_write[i], NULL, *writer1, (void*)i);  // Create writer threads
                }
                for(i = 0; i < R; i++) {
                    pthread_create(&thread_reader[i], NULL, *reader1, (void*)i);  // Create reader threads
                }

                // Wait for all writer threads to finish
                for(i = 0; i < W; i++) {
                    pthread_join(thread_write[i], NULL);
                }

                // Wait for all reader threads to finish
                for(i = 0; i < R; i++) {
                    pthread_join(thread_reader[i], NULL);
                }
                break;
            case 2:
                exit(1);  // Exit the program
        }
    } while(op != 2);  // Repeat until user chooses to exit

    pthread_mutex_destroy(&x);  // Destroy the mutex
    sem_destroy(&wsem);         // Destroy the semaphore
}

void *reader1(void *a) {
    int r = (int)a;
    int i = 0;
    while(i < 5) {
        pthread_mutex_lock(&x);  // Lock mutex to safely update readcount
        readcount++;

        if(readcount == 1)  // First reader locks the writer
            sem_wait(&wsem); // Wait for writer

        pthread_mutex_unlock(&x); // Unlock mutex

        printf("\t\t reader %d is reading :%d \n", r, s); // Simulate reading

        pthread_mutex_lock(&x);
        readcount--;

        if(readcount == 0)  // Last reader unlocks the writer
            sem_post(&wsem); // Allow writers to access

        pthread_mutex_unlock(&x);
        sleep(rand() % 10);  // Simulate reading time
        i++;
    }
}

void *writer1(void *a) {
    int w = (int)a;
    int i = 0;
    while(i < 2) {
        sem_wait(&wsem);  // Wait for write access

        s += 5; // Simulate writing (modifying the shared resource)
        printf("writer %d is writing : %d \n", w, s);

        sem_post(&wsem);  // Release write access

        sleep(rand() % 10);  // Simulate writing time
        i++;
    }
}
