#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LEN 100
#define MAX_THREADS 5

typedef struct {
  FILE *file;
  const char *word;
  int *count;
  long start;
  long end;
} ThreadData;

void *count_word_occurrences(void *arg) {
  ThreadData *data = (ThreadData *)arg;
  fseek(data->file, data->start, SEEK_SET);

  char temp[MAX_WORD_LEN];
  int local_count = 0;
  long current_pos = ftell(data->file);

  while (current_pos < data->end && fscanf(data->file, "%s", temp) != EOF) {
    if (strcmp(temp, data->word) == 0) {
      local_count++;
    }
    current_pos = ftell(data->file);
  }

  *data->count = local_count;
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Usage: %s <file.txt> <word> <threads>\n", argv[0]);
    return 1;
  }

  int num_threads = atoi(argv[3]);
  if (num_threads > MAX_THREADS) {
    num_threads = MAX_THREADS;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);

  pthread_t threads[MAX_THREADS];
  ThreadData data[MAX_THREADS];
  int counts[MAX_THREADS] = {0};
  long block_size = file_size / num_threads;

  clock_t start_time = clock();

  for (int i = 0; i < num_threads; i++) {
    data[i].file = file;
    data[i].word = argv[2];
    data[i].count = &counts[i];
    data[i].start = i * block_size;
    data[i].end = (i == num_threads - 1) ? file_size : (i + 1) * block_size;

    pthread_create(&threads[i], NULL, count_word_occurrences, &data[i]);
  }

  int total_count = 0;
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
    total_count += counts[i];
  }

  clock_t end_time = clock();
  fclose(file);

  double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("The word '%s' appears %d times.\n", argv[2], total_count);
  printf("Time taken with %d threads: %f seconds\n", num_threads, time_spent);

  return 0;
}
