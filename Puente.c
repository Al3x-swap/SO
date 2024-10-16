#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semáforos y variables globales
sem_t semaforo_este, semaforo_oeste;
int contador_este = 0, contador_oeste = 0;
pthread_mutex_t lock;

void *coche_este(void *arg) {
    int id = *((int *)arg);
    sleep(rand() % 20);  // Espera aleatoria antes de intentar cruzar

    pthread_mutex_lock(&lock);
    contador_este++;
    if (contador_oeste == 0) {
        sem_post(&semaforo_este);
    }
    pthread_mutex_unlock(&lock);

    sem_wait(&semaforo_este);  // Espera para entrar al puente
    printf("Coche %d del ESTE entra al puente\n", id);
    sleep(1);  // Cruza el puente
    printf("Coche %d del ESTE sale del puente\n", id);

    pthread_mutex_lock(&lock);
    contador_este--;
    if (contador_este == 0 && contador_oeste > 0) {
        sem_post(&semaforo_oeste);  // Da paso a los coches del oeste
    } else {
        sem_post(&semaforo_este);  // Da paso a los coches del este
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *coche_oeste(void *arg) {
    int id = *((int *)arg);
    sleep(rand() % 20);  // Espera aleatoria antes de intentar cruzar

    pthread_mutex_lock(&lock);
    contador_oeste++;
    if (contador_este == 0) {
        sem_post(&semaforo_oeste);
    }
    pthread_mutex_unlock(&lock);

    sem_wait(&semaforo_oeste);  // Espera para entrar al puente
    printf("Coche %d del OESTE entra al puente\n", id);
    sleep(1);  // Cruza el puente
    printf("Coche %d del OESTE sale del puente\n", id);

    pthread_mutex_lock(&lock);
    contador_oeste--;
    if (contador_oeste == 0 && contador_este > 0) {
        sem_post(&semaforo_este);  // Da paso a los coches del este
    } else {
        sem_post(&semaforo_oeste);  // Da paso a los coches del oeste
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t coches_este[50], coches_oeste[50];
    int ids_este[50], ids_oeste[50];

    // Inicialización de semáforos y mutex
    sem_init(&semaforo_este, 0, 0);
    sem_init(&semaforo_oeste, 0, 0);
    pthread_mutex_init(&lock, NULL);

    // Creación de hilos de coches
    for (int i = 0; i < 50; i++) {
        ids_este[i] = i + 1;
        ids_oeste[i] = i + 1;
        pthread_create(&coches_este[i], NULL, coche_este, &ids_este[i]);
        pthread_create(&coches_oeste[i], NULL, coche_oeste, &ids_oeste[i]);
    }

    // Espera a que los hilos terminen
    for (int i = 0; i < 50; i++) {
        pthread_join(coches_este[i], NULL);
        pthread_join(coches_oeste[i], NULL);
    }

    // Destrucción de semáforos y mutex
    sem_destroy(&semaforo_este);
    sem_destroy(&semaforo_oeste);
    pthread_mutex_destroy(&lock);

    return 0;
}