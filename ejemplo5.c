#include <stdio.h>
#include <pthread.h>

// Estructura para almacenar el ID y el nombre de cada hilo
typedef struct {
    int id;
    char nombre[20];
} HiloInfo;

// Función que será ejecutada por cada hilo pesado
void *funcion_hilo_pesado(void *arg) {
    HiloInfo *info = (HiloInfo *)arg;
    printf("Hilo pesado ejecutado: %s con # %d\n", info->nombre, info->id); // Imprimir el nombre y el ID del hilo pesado
    pthread_exit(NULL); // Terminar el hilo pesado
}

int main() {
    pthread_t hilos[4]; // Array para almacenar los identificadores de los hilos pesados
    HiloInfo info[4] = { // Array de estructuras HiloInfo
        {1, "Diego"},
        {2, "Italuu"},
        {3, "Jairy"},
        {4, "Josh"}
    };

    // Crear hilos pesados
    for (int i = 0; i < 4; i++) {
        pthread_create(&hilos[i], NULL, funcion_hilo_pesado, (void *)&info[i]); // Pasar un puntero a la estructura HiloInfo
    }

    // Esperar la finalización de los hilos
    for (int i = 0; i < 4; i++) {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo pesado con el ID correspondiente termine
    }

    return 0;
}