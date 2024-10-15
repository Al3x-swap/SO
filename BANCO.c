#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Variable global para el saldo
int saldo = 1000;  // Saldo inicial en la cuenta bancaria

// Mutex para proteger el acceso al saldo
pthread_mutex_t mutex_saldo;

// Función para realizar un depósito
void* deposito(void* arg) {
    int cantidad = *(int*) arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_saldo);  // Bloquear el acceso al saldo
        saldo += cantidad;
        printf("Depósito realizado: +%d, Saldo actual: %d\n", cantidad, saldo);
        pthread_mutex_unlock(&mutex_saldo);  // Desbloquear el acceso al saldo
        sleep(1);  // Simula tiempo entre depósitos
    }
    return NULL;
}

// Función para realizar un retiro
void* retiro(void* arg) {
    int cantidad = *(int*) arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_saldo);  // Bloquear el acceso al saldo
        if (saldo >= cantidad) {
            saldo -= cantidad;
            printf("Retiro realizado: -%d, Saldo actual: %d\n", cantidad, saldo);
        } else {
            printf("Saldo insuficiente para retirar %d, Saldo actual: %d\n", cantidad, saldo);
        }
        pthread_mutex_unlock(&mutex_saldo);  // Desbloquear el acceso al saldo
        sleep(1);  // Simula tiempo entre retiros
    }
    return NULL;
}

int main() {
    // Inicializar el mutex
    pthread_mutex_init(&mutex_saldo, NULL);

    // Crear los hilos
    pthread_t hilo_deposito, hilo_retiro;
    int cantidad_deposito = 500;
    int cantidad_retiro = 300;

    // Crear los hilos de depósito y retiro
    pthread_create(&hilo_deposito, NULL, deposito, &cantidad_deposito);
    pthread_create(&hilo_retiro, NULL, retiro, &cantidad_retiro);

    // Esperar a que ambos hilos terminen
    pthread_join(hilo_deposito, NULL);
    pthread_join(hilo_retiro, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex_saldo);

    return 0;
}

//Explicación del código:
//Saldo global: La variable saldo representa el saldo de la cuenta bancaria y es compartida por ambos hilos.
//Mutex (candado): Se utiliza pthread_mutex_t para proteger el acceso a la variable saldo, asegurando que los hilos de retiro y depósito no accedan a ella simultáneamente.
//Funciones atómicas: Las funciones deposito y retiro bloquean el acceso a saldo con pthread_mutex_lock() antes de modificarlo, y lo liberan con pthread_mutex_unlock() después de la operación.
//Hilos en paralelo: Los hilos se ejecutan en paralelo, realizando múltiples depósitos y retiros de forma segura.
