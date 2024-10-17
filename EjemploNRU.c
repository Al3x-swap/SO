#include <stdio.h>

#define NUM_PAGINAS 4

// Estructura para representar una página
typedef struct {
    int id;        // ID de la página
    int referencia; // Bit de referencia (R)
    int modificada; // Bit de modificación (M)
} Pagina;

// Función para clasificar las páginas en categorías NRU
int obtenerCategoria(Pagina p) {
    if (p.referencia == 0 && p.modificada == 0)
        return 0; // Categoría 1: No referenciada, no modificada
    if (p.referencia == 0 && p.modificada == 1)
        return 1; // Categoría 2: No referenciada, modificada
    if (p.referencia == 1 && p.modificada == 0)
        return 2; // Categoría 3: Referenciada, no modificada
    return 3;     // Categoría 4: Referenciada, modificada
}

// Función para reemplazar la página en la categoría más baja
int reemplazarPagina(Pagina paginas[], Pagina nuevaPagina) {
    int minCategoria = 4; // La categoría más alta posible es 3
    int paginaAReemplazar = -1;

    // Encuentra la página con la categoría más baja
    for (int i = 0; i < NUM_PAGINAS; i++) {
        int categoria = obtenerCategoria(paginas[i]);
        if (categoria < minCategoria) {
            minCategoria = categoria;
            paginaAReemplazar = i;
        }
    }

    // Reemplaza la página en la categoría más baja
    if (paginaAReemplazar != -1) {
        printf("Reemplazando página %d en la categoría %d por la nueva página %d.\n",
               paginas[paginaAReemplazar].id, minCategoria, nuevaPagina.id);
        paginas[paginaAReemplazar] = nuevaPagina;
    }

    return paginaAReemplazar;
}

int main() {
    // Páginas existentes con sus bits de referencia y modificación
    Pagina paginas[NUM_PAGINAS] = {
        {1, 0, 0}, // Página A: No referenciada, no modificada
        {2, 1, 0}, // Página B: Referenciada, no modificada
        {3, 0, 1}, // Página C: No referenciada, modificada
        {4, 1, 1}  // Página D: Referenciada, modificada
    };

    // Nueva página a cargar
    Pagina nuevaPagina = {5, 0, 0}; // Página E: No referenciada, no modificada

    // Imprime el estado inicial de las páginas
    printf("Estado inicial de las páginas:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página %d: R=%d, M=%d\n", paginas[i].id, paginas[i].referencia, paginas[i].modificada);
    }

    // Reemplaza la página en la categoría más baja
    reemplazarPagina(paginas, nuevaPagina);

    // Imprime el estado final de las páginas
    printf("\nEstado final de las páginas:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página %d: R=%d, M=%d\n", paginas[i].id, paginas[i].referencia, paginas[i].modificada);
    }

    return 0;
}

//Estado inicial de las páginas:
//Página 1: R=0, M=0
//Página 2: R=1, M=0
//Página 3: R=0, M=1
//Página 4: R=1, M=1
//Reemplazando página 1 en la categoría 0 por la nueva página 5.

//Estado final de las páginas:
//Página 5: R=0, M=0
//Página 2: R=1, M=0
//Página 3: R=0, M=1
//Página 4: R=1, M=1

