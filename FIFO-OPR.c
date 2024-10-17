#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4  // Número de frames (páginas físicas en memoria)
#define NUM_PAGES 10  // Número total de páginas virtuales

// Estructura para un frame de página en memoria física
typedef struct Frame {
    int page;           // Número de página almacenada en el frame (valor -1 si está vacío)
    bool valid;         // Indica si el frame está ocupado (true) o vacío (false)
    struct Frame *prev; // Puntero al frame previo (para lista doblemente enlazada)
    struct Frame *next; // Puntero al frame siguiente (para lista doblemente enlazada)
} Frame;

// Estructura para la lista de frames en memoria física
typedef struct FrameList {
    int numFrames;      // Número de frames actualmente ocupados
    Frame *head;        // Puntero al primer frame de la lista
    Frame *tail;        // Puntero al último frame de la lista
} FrameList;

// Función para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;   // Inicialmente no hay página asignada
        frame->valid = false;
        frame->prev = NULL;
        frame->next = NULL;
    }
    return frame;
}

// Función para inicializar la lista de frames en memoria física
FrameList* createFrameList() {
    FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
    if (frameList != NULL) {
        frameList->numFrames = 0;
        frameList->head = NULL;
        frameList->tail = NULL;
    }
    return frameList;
}

// Función para insertar un frame al frente de la lista (más recientemente usado)
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        // Lista vacía
        frameList->head = frame;
        frameList->tail = frame;
    } else {
        // Insertar al frente de la lista
        frame->next = frameList->head;
        frameList->head->prev = frame;
        frameList->head = frame;
    }
    frameList->numFrames++;
}

// Función para eliminar un frame de la lista (menos recientemente usado)
void removeFrame(FrameList *frameList, Frame *frame) {
    if (frame->prev != NULL) {
        frame->prev->next = frame->next;
    } else {
        frameList->head = frame->next;
    }
    if (frame->next != NULL) {
        frame->next->prev = frame->prev;
    } else {
        frameList->tail = frame->prev;
    }
    frameList->numFrames--;
    free(frame);
}

// Función para buscar un frame específico por número de página
Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    while (current != NULL) {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para cargar una página en la memoria utilizando el algoritmo OPR
void loadPage(FrameList *frameList, int *futurePages, int futureLength) {
    // Si ya está en memoria, no hace nada
    Frame *frameInMemory = findFrame(frameList, futurePages[0]);
    if (frameInMemory != NULL) {
        return;
    }

    // Si no hay espacio en memoria, reemplazamos
    if (frameList->numFrames == NUM_FRAMES) {
        // Encontrar el frame a reemplazar utilizando OPR
        Frame *frameToReplace = frameList->head;
        int maxDistance = -1;
        Frame *current = frameList->head;

        while (current != NULL) {
            int distance = -1;  // Si no se encuentra la página en el futuro, se reemplaza
            for (int i = 0; i < futureLength; i++) {
                if (current->page == futurePages[i]) {
                    distance = i;
                    break;
                }
            }

            if (distance == -1) {
                frameToReplace = current;
                break;  // Esta página no se utilizará más, la reemplazamos
            } else if (distance > maxDistance) {
                maxDistance = distance;
                frameToReplace = current;
            }

            current = current->next;
        }

        // Reemplazamos la página
        removeFrame(frameList, frameToReplace);
    }

    // Insertamos la nueva página en memoria
    Frame *newFrame = createFrame();
    newFrame->page = futurePages[0];
    newFrame->valid = true;
    insertFrame(frameList, newFrame);
}

// Función para imprimir el estado actual de la lista de frames (solo para fines de depuración)
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Página: %d, Estado: %s\n", current->page, current->valid ? "Ocupado" : "Vacío");
        current = current->next;
    }
    printf("\n");
}

int main() {
    FrameList *frameList = createFrameList();

    // Referencia futura de páginas a cargar (para simular OPR en el sistema)
    int futurePages[NUM_PAGES] = {5, 0, 1, 2, 3, 4, 5};

    // Simular la carga de varias páginas a memoria física utilizando OPR
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Cargando página: %d\n", futurePages[i]);
        loadPage(frameList, futurePages + i, NUM_PAGES - i);  // Cargar página considerando el futuro
        printFrameList(frameList);  // Imprime el estado actual de los frames
    }

    // Liberar la memoria utilizada por la lista de frames
    Frame *current = frameList->head;
    while (current != NULL) {
        Frame *next = current->next;
        free(current);
        current = next;
    }
    free(frameList);

    return 0;
}
