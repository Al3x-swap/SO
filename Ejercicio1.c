//Ejemplo 1:

            //En este modelo, varios hilos de usuario se mapean a un número menor de hilos del sistema operativo, permitiendo una implementación más eficiente y adaptativa de hilos.   

        #include <stdio.h>
        #include <pthread.h>

        // Función que será ejecutada por cada hilo
        void *funcion_hilo(void *arg) {
            printf("Hilo ejecutado: %d\n", *((int *) arg));                                         // Imprimir el ID del hilo
            pthread_exit(NULL);                                                                     // Terminar el hilo
        }

        int main() {
            pthread_t hilos[5];                                                                     // Array para almacenar los identificadores de los hilos
            int ids[] = {1, 2, 3, 4, 5};                                                               // Array de IDs de los hilos

            // Crear hilos
            for (int i = 0; i < 5; i++) {
                pthread_create(&hilos[i], NULL, funcion_hilo, (void *) &ids[i]);                    // Crear un nuevo hilo
            }

            // Esperar la finalización de los hilos
            for (int i = 0; i < 5; i++) {
                pthread_join(hilos[i], NULL);                                                       // Esperar a que el hilo con el ID correspondiente termine
            }

            return 0;
        }

