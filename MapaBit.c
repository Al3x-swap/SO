#include <stdio.h>

int main() {
    int NUM_BLOCKS;  // Variable para almacenar el número de bloques
    
    // Solicitar al usuario que ingrese el número de bloques
    printf("Ingrese el número de bloques: ");
    scanf("%d", &NUM_BLOCKS);
    
    // Crear un array de bloques con tamaño NUM_BLOCKS
    int bitmap[NUM_BLOCKS];
    
    // Solicitar al usuario que ingrese los valores del mapa de bits
    printf("Ingrese los valores del mapa de bits (0 o 1) para cada bloque:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("Bloque %d: ", i);
        scanf("%d", &bitmap[i]);
    }

    // Función para mostrar el estado de un mapa de bits
    void mostrarMapaDeBits(int bitmap[], int numBlocks) {
        printf("Mapa de bits:\n");
        for (int i = 0; i < numBlocks; i++) {
            printf("%d ", bitmap[i]);
        }
        printf("\n");
    }

    // Función para mostrar los bloques que están libres (valor 0)
    void mostrarListaEspacioLibre(int bitmap[], int numBlocks) {
        printf("Lista de espacio libre:\n");
        for (int i = 0; i < numBlocks; i++) {
            if (bitmap[i] == 0) {
                printf("Bloque %d libre\n", i);
            }
        }
    }
    
    // Mostrar el mapa de bits
    mostrarMapaDeBits(bitmap, NUM_BLOCKS);
    
    // Mostrar la lista de bloques libres
    mostrarListaEspacioLibre(bitmap, NUM_BLOCKS);
    
    return 0;
}
