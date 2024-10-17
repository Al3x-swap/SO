#include <stdio.h>

#define NUM_PAGINAS 4

// Estructura para representar una página
typedef struct {
    int id;        // ID de la página
    int frecuencia; // Número de veces que la página ha sido accedida (frecuencia de uso)
} Pagina;

// Función para encontrar la página con menor frecuencia de uso
int reemplazarPaginaLFU(Pagina paginas[], Pagina nuevaPagina) {
    int minFrecuencia = paginas[0].frecuencia;
    int paginaAReemplazar = 0;

    // Encuentra la página con la menor frecuencia de uso
    for (int i = 1; i < NUM_PAGINAS; i++) {
        if (paginas[i].frecuencia < minFrecuencia) {
            minFrecuencia = paginas[i].frecuencia;
            paginaAReemplazar = i;
        }
    }

    // Reemplaza la página con menor frecuencia
    printf("Reemplazando página %d (frecuencia: %d) por la nueva página %d.\n",
           paginas[paginaAReemplazar].id, paginas[paginaAReemplazar].frecuencia, nuevaPagina.id);
    
    paginas[paginaAReemplazar] = nuevaPagina;

    return paginaAReemplazar;
}

int main() {
    // Páginas existentes con sus frecuencias de uso
    Pagina paginas[NUM_PAGINAS] = {
        {1, 5}, // Página A: frecuencia 5
        {2, 3}, // Página B: frecuencia 3
        {3, 7}, // Página C: frecuencia 7
        {4, 2}  // Página D: frecuencia 2
    };

    // Nueva página a cargar
    Pagina nuevaPagina = {5, 1}; // Página E con frecuencia inicial 1

    // Imprime el estado inicial de las páginas
    printf("Estado inicial de las páginas:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página %d: Frecuencia=%d\n", paginas[i].id, paginas[i].frecuencia);
    }

    // Reemplaza la página con la menor frecuencia de uso
    reemplazarPaginaLFU(paginas, nuevaPagina);

    // Imprime el estado final de las páginas
    printf("\nEstado final de las páginas:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página %d: Frecuencia=%d\n", paginas[i].id, paginas[i].frecuencia);
    }

    return 0;
}


//Salida:
//Estado inicial de las páginas:
//Página 1: Frecuencia=5
//Página 2: Frecuencia=3
//Página 3: Frecuencia=7
//Página 4: Frecuencia=2
//Reemplazando página 4 (frecuencia: 2) por la nueva página 5.

//Estado final de las páginas:
//Página 1: Frecuencia=5
//Página 2: Frecuencia=3
//Página 3: Frecuencia=7
//Página 5: Frecuencia=1

