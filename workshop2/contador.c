#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char archivo[100] = "mucho_texto.txt";
    char palabra[100] = "they";
    char linea[1000];
    int contador = 0;
    FILE *archivo_txt;

    printf("Buscando para %s la palabra %s...\n\n", archivo, palabra);
	
    //printf("Ingrese el nombre del archivo (.txt): ");
    //scanf("%s", archivo);

    //printf("Ingrese la palabra que desea contar: ");
    //scanf("%s", palabra);

    // Tomar el tiempo de inicio
    clock_t inicio = clock();

    archivo_txt = fopen(archivo, "r");

    if (archivo_txt == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo_txt)) {
        char *token = strtok(linea, " \t\n");

        while (token != NULL) {
            if (strcmp(token, palabra) == 0) {
                contador++;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(archivo_txt);

    // Tomar el tiempo de finalización
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("La palabra '%s' aparece %d veces en el archivo '%s'.\n", palabra, contador, archivo);
    printf("Tiempo de ejecución: %f segundos\n", tiempo);

    return 0;
}
