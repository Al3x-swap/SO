#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void tarea1(const char *filename, int pipe1[], int pipe2[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo el archivo");
        exit(1);
    }

    char line[256];
    int line_number = 1;
    while (fgets(line, sizeof(line), file)) {
        if (line_number % 2 == 0) {
            // Escribir en la tubería 1 las líneas pares
            write(pipe1[1], line, strlen(line));
        } else {
            // Escribir en la tubería 2 las líneas impares
            write(pipe2[1], line, strlen(line));
        }
        line_number++;
    }
    fclose(file);

    // Cerrar los extremos de escritura
    close(pipe1[1]);
    close(pipe2[1]);
}

void tarea2(int pipe1[], int pipe3[], const char *word) {
    // Redirigir la entrada de la tubería 1
    dup2(pipe1[0], STDIN_FILENO);
    // Redirigir la salida a la tubería 3
    dup2(pipe3[1], STDOUT_FILENO);
    
    // Ejecutar grep
    execlp("grep", "grep", word, NULL);

    // Si execlp falla
    perror("Error ejecutando grep");
    exit(1);
}

void tarea3(int pipe2[], int pipe3[], const char *word) {
    // Redirigir la entrada de la tubería 2
    dup2(pipe2[0], STDIN_FILENO);
    // Redirigir la salida a la tubería 3
    dup2(pipe3[1], STDOUT_FILENO);

    // Ejecutar grep
    execlp("grep", "grep", word, NULL);

    // Si execlp falla
    perror("Error ejecutando grep");
    exit(1);
}

void tarea4(int pipe3[]) {
    // Redirigir la entrada de la tubería 3
    dup2(pipe3[0], STDIN_FILENO);

    // Ejecutar sort
    execlp("sort", "sort", NULL);

    // Si execlp falla
    perror("Error ejecutando sort");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <archivo> <palabra1> <palabra2>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    const char *word1 = argv[2];
    const char *word2 = argv[3];

    // Crear las tuberías
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    // Crear procesos
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Proceso hijo 1: Tarea 1
        close(pipe1[0]); // Cerrar el extremo de lectura de la tubería 1
        close(pipe2[0]); // Cerrar el extremo de lectura de la tubería 2
        close(pipe3[0]); // Cerrar los extremos de la tubería 3
        close(pipe3[1]);
        tarea1(filename, pipe1, pipe2);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Proceso hijo 2: Tarea 2
        close(pipe1[1]); // Cerrar el extremo de escritura de la tubería 1
        close(pipe2[0]); close(pipe2[1]); // No usar la tubería 2
        close(pipe3[0]); // Cerrar el extremo de lectura de la tubería 3
        tarea2(pipe1, pipe3, word1);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        // Proceso hijo 3: Tarea 3
        close(pipe1[0]); close(pipe1[1]); // No usar la tubería 1
        close(pipe2[1]); // Cerrar el extremo de escritura de la tubería 2
        close(pipe3[0]); // Cerrar el extremo de lectura de la tubería 3
        tarea3(pipe2, pipe3, word2);
        exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        // Proceso hijo 4: Tarea 4
        close(pipe1[0]); close(pipe1[1]); // No usar la tubería 1
        close(pipe2[0]); close(pipe2[1]); // No usar la tubería 2
        close(pipe3[1]); // Cerrar el extremo de escritura de la tubería 3
        tarea4(pipe3);
        exit(0);
    }

    // Cerrar todos los extremos de las tuberías en el proceso padre
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    close(pipe3[0]); close(pipe3[1]);

    // Esperar a que los hijos terminen
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}