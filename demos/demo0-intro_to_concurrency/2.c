#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define COUNT_TO 1e7 // 10_000_000

static volatile int counter = 0;
pthread_mutex_t mutex;

void* add_to_counter(void* arg) {
  printf(
    "%c: begin (counter = %d)\n", 
    *(char*) arg,
    counter
  );
  
  for (int i = 0; i < COUNT_TO; i++) {
    // pthread_mutex_lock(&mutex);
    counter++; // counter = counter + 1;
    // pthread_mutex_unlock(&mutex);
  }
  
  printf(
    "%c: done (counter = %d)\n", 
    *(char*) arg,
    counter
  );
  
  return NULL;
}

int main(int argc, char* argv[]) {

  pthread_t p[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);
  char labels[NUM_THREADS];

  printf("main: begin (counter = %d)\n", counter);

  for (int i = 0; i < NUM_THREADS; i++) {
    labels[i] = 'A' + i;
    pthread_create(
      &p[i],
      NULL,
      add_to_counter,
      &labels[i]
    );
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(p[i], NULL);
  }
  
  printf("main: done with both (counter = %d)\n", counter);
  return 0;
}


