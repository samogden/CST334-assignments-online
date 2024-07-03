//
// Created by Sam Ogden on 8/8/23.
//

/**
Author: Ichiro Miyasato
Assignment: Programming Assignment 2
Date: 02 July 2024
 */

#include "student_code.h"
#include "stdio.h"


void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started) {
  //todo done
  stats->num_processes_started += 1;
  stats->sum_of_response_time = stats->sum_of_response_time + time_started - p->entry_time;
}
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed) {
  //todo done
  stats->num_processes_completed += 1;
  stats->sum_of_turnaround_times = stats->sum_of_turnaround_times + time_completed - p->entry_time;
}

void finalize_stats(SCHEDULER_STATS* stats) {
  //todo done
  stats->average_turnaround_time = (stats->sum_of_turnaround_times) / (stats->num_processes_completed);
  stats->average_response_time = (stats->sum_of_response_time) / (stats->num_processes_started);
}

int compare_priority(PROCESS p1, PROCESS p2) {
  //todo done
  return (int)p1.priority - (int)p2.priority;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo done
  p = pl->processes[0];
  for (int i = 1; i < pl->num_processes; i++) {
    if (p->entry_time - pl->processes[i]->entry_time > 0) {
        p = pl->processes[i];
    }
  }
  return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo done
  p = get_next(pl);
  return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo done
  p = pl->processes[0];
  for (int i = 1; i < pl->num_processes; i++) {
    if (p->duration - pl->processes[i]->duration > 0) {
        p = pl->processes[i];
    }
  }
  return p;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  p = get_minimum(pl, compare_priority);
  return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo done
  p = pl->processes[0];
  for (int i = 1; i < pl->num_processes; i++) {
    if (p->entry_time - pl->processes[i]->entry_time < 0) {
        p = pl->processes[i];
    }
  }
  return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo done
  p = pl->processes[0];
  for (int i = 1; i < pl->num_processes; i++) {
    if (p->time_remaining - pl->processes[i]->time_remaining > 0) {
        p = pl->processes[i];
    }
  }
  return p;
}
