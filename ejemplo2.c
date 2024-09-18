 //Ejemplo 1:

            //En este modelo, varios hilos de usuario se mapean a un número menor de hilos del sistema operativo, permitiendo una implementación más eficiente y adaptativa de hilos.   

        #include <stdio.h>
        #include <pthread.h>
	#include <string.h>
        // Función que será ejecutada por cada hilo
        void *funcion_hilo(void *arg) {
        char *hilo_nombres=(char *) arg;
            printf("Hilo ejecutado: %s\n", hilo_nombres);                                         // Imprimir el ID del hilo
            pthread_exit(NULL);                                                                     // Terminar el hilo
        }

        int main() {
            pthread_t hilos[4];                                                                     // Array para almacenar los identificadores de los hilos
            char *nombres[] = {"Ita", "Josh", "Diego", "Jairy"};                                                               // Array de IDs de los hilos

            // Crear hilos
            for (int i = 0; i < 4; i++) {
                pthread_create(&hilos[i], NULL, funcion_hilo, (void *) nombres[i]);                    // Crear un nuevo hilo
            }

            // Esperar la finalización de los hilos
            for (int i = 0; i < 4; i++) {
                pthread_join(hilos[i], NULL);                                                       // Esperar a que el hilo con el ID correspondiente termine
            }

            return 0;
        }
