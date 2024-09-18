#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_ARTICULOS 100
#define MAX_LONGITUD 100

char *articulos[MAX_ARTICULOS];
int contador = 0;
pthread_mutex_t mutex;

void *ordenar(void *arg) {
    pthread_mutex_lock(&mutex);
    // Ordenamiento burbuja
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (strcmp(articulos[i], articulos[j]) > 0) {
                char *temp = articulos[i];
                articulos[i] = articulos[j];
                articulos[j] = temp;
            }
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    printf("Ingrese el número de artículos (máximo %d): ", MAX_ARTICULOS);
    scanf("%d", &contador);
    getchar();  // Limpiar el buffer

    if (contador > MAX_ARTICULOS || contador <= 0) {
        printf("Número de artículos no válido.\n");
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);

    // Ingreso de artículos
    for (int i = 0; i < contador; i++) {
        articulos[i] = malloc(MAX_LONGITUD * sizeof(char));
        if (articulos[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria.\n");
            return 1;
        }
        printf("Ingrese el artículo %d: ", i + 1);
        fgets(articulos[i], MAX_LONGITUD, stdin);
        articulos[i][strcspn(articulos[i], "\n")] = 0;  // Eliminar el salto de línea
    }

    pthread_t hilo;
    pthread_create(&hilo, NULL, ordenar, NULL);
    pthread_join(hilo, NULL);

    // Mostrar artículos ordenados
    printf("\nArtículos ordenados:\n");
    for (int i = 0; i < contador; i++) {
        printf("%s\n", articulos[i]);
        free(articulos[i]);  // Liberar memoria
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
