
#include "tests.h"
#include <common.h>

void test_1proc_0entry(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats) {

  PROCESS* p0 = create_process(5.0f, 0.0f, 0.0f);

  PROCESS_LIST* pl = create_process_list();
  add_process_to_tail(pl, p0);

  main_simulation_loop(params, stats, pl);

}

void test_2proc_0entry_0entry(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats) {

  PROCESS* p0 = create_process(5.0f, 0, 0.0f);
  PROCESS* p1 = create_process(5.0f, 1, 0.0f);

  PROCESS_LIST* pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);

  main_simulation_loop(params, stats, pl);
  // print_stats(*stats);
}

void test_2proc_0entry_1entry(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats) {

  // Question: What is this function doing and where is it used?

  PROCESS* p0 = create_process(5.0f, 0, 0.0f);
  PROCESS* p1 = create_process(5.0f, 1, 1.0f);

  PROCESS_LIST* pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);

  main_simulation_loop(params, stats, pl);
  // print_stats(*stats);
}

void test_5proc(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats) {

  PROCESS* p0 = create_process(5.0f, 6, 6.0f);
  PROCESS* p1 = create_process(9.0f, 1, 5.0f);
  PROCESS* p2 = create_process(6.0f, 3, 1.0f);
  PROCESS* p3 = create_process(2.0f, 5, 3.0f);
  PROCESS* p4 = create_process(7.0f, 1, 1.0f);

  PROCESS_LIST* pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  add_process_to_tail(pl, p2);
  add_process_to_tail(pl, p3);
  add_process_to_tail(pl, p4);

  main_simulation_loop(params, stats, pl);
  // print_stats(*stats);
}
