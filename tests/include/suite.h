#ifndef CHECK_SUITE_H
#define CHECK_SUITE_H

struct Suite;
struct SRunner;

typedef void (*test_func)(int);

SRunner *
suite_runner_create(Suite *sr);

int
run_and_report(SRunner *sr);

#endif


