#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 5

typedef struct {
    char *buffer;
    const char *word;
    int start;
    int end;
    int count;
} ThreadArg;

// Función que utiliza cada hilo para contar apariciones de la palabra
void *count_occurrences(void *arg) {
    ThreadArg *data = (ThreadArg *)arg;
    int count = 0;
    char *token;
    char *saveptr;  // Para uso seguro en ambientes multihilo

    for (int i = data->start; i <= data->end; i++) {
        if (i == data->start) {
            token = strtok_r(data->buffer + i, " \t\n.,;:!?()[]{}", &saveptr);
        } else {
            token = strtok_r(NULL, " \t\n.,;:!?()[]{}", &saveptr);
        }

        while (token != NULL) {
            if (strcmp(token, data->word) == 0) {
                count++;
            }
            token = strtok_r(NULL, " \t\n.,;:!?()[]{}", &saveptr);
        }
    }

    data->count = count;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <archivo> <palabra> <num_hilos>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    const char *word = argv[2];
    int num_threads = atoi(argv[3]);
    if (num_threads < 1 || num_threads > MAX_THREADS) {
        fprintf(stderr, "Número de hilos debe ser entre 1 y %d.\n", MAX_THREADS);
        return 1;
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Leer el contenido completo del archivo en memoria
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);
    buffer[fsize] = 0;  // Asegurar que la cadena está terminada

    // Crear y configurar argumentos para cada hilo
    pthread_t threads[MAX_THREADS];
    ThreadArg args[MAX_THREADS];
    int part_size = fsize / num_threads;

    clock_t start = clock();

    for (int i = 0; i < num_threads; i++) {
        args[i].buffer = buffer;
        args[i].word = word;
        args[i].start = i * part_size;
        args[i].end = (i == num_threads - 1) ? fsize : (i + 1) * part_size - 1;
        pthread_create(&threads[i], NULL, count_occurrences, &args[i]);
    }

    // Esperar que todos los hilos terminen y sumar los resultados
    int total_count = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_count += args[i].count;
    }

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("La palabra '%s' aparece %d veces en el archivo '%s'.\n", word, total_count, filepath);
    printf("Tiempo de ejecución con %d hilos: %f segundos.\n", num_threads, time_taken);

    free(buffer);
    return 0;
}

