#include <stdio.h>

#define MAX_DISK_SIZE 50  // Tamaño del disco ajustado

// Función que realiza la asignación de bloques contiguos en el disco
void asignarArchivo(int disco[], int inicio, int tamanio) {
    // Verifica si hay suficiente espacio disponible a partir del bloque de inicio
    if (inicio + tamanio > MAX_DISK_SIZE) {
        printf("Error: No hay suficiente espacio en el disco para asignar el archivo.\n");
        return;
    }

    // Recorre los bloques del disco e intenta asignar los bloques al archivo
    for (int i = inicio; i < inicio + tamanio; i++) {
        if (disco[i] == 1) {  // Si el bloque ya está ocupado
            printf("Error: Bloque %d ya esta ocupado. Asignacion fallida.\n", i);
            return;
        }
        disco[i] = 1;  // Marca el bloque como ocupado
    }
    printf("Archivo asignado exitosamente de %d bloques a partir del bloque %d.\n", tamanio, inicio);
}

// Función que muestra el estado actual del disco
void mostrarEstadoDisco(int disco[]) {
    printf("Estado actual del disco:\n");
    for (int i = 0; i < MAX_DISK_SIZE; i++) {
        printf("%d ", disco[i]);
    }
    printf("\n");
}

int main() {
    // Se define un disco con un tamaño flexible y se inicializa con bloques libres
    int disco[MAX_DISK_SIZE] = {0};

    // Asignación de un archivo de 6 bloques, comenzando desde el bloque 5
    asignarArchivo(disco, 5, 6);
    mostrarEstadoDisco(disco);

    // Intento de asignar otro archivo de 4 bloques, comenzando desde el bloque 20
    asignarArchivo(disco, 20, 4);
    mostrarEstadoDisco(disco);

    // Asignación de un archivo de 3 bloques, comenzando desde el bloque 10
    asignarArchivo(disco, 10, 3);
    mostrarEstadoDisco(disco);

    // Intento de asignar un archivo con más bloques de los que el disco puede contener
    asignarArchivo(disco, 45, 10);
    mostrarEstadoDisco(disco);

    return 0;
}
