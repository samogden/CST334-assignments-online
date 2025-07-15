#include "pthread.h"

typedef struct counter_t {
  int value;
  pthread_mutex_t mutex;
} counter_t;

void counter_init(counter_t* counter);
void counter_increment(counter_t* counter);
int counter_get(const counter_t* counter);