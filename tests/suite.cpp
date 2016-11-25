#include "suite.h"

#include <check.h>

SRunner *
suite_runner_create(Suite *s)
{
  SRunner *sr;

  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  return sr;
}

int
run_and_report(SRunner *sr)
{
  int number_failed;

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}

