/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "../src/orcania.h"

START_TEST(test_o_malloc)
{
  void * var;
  var = malloc(8);
  ck_assert_ptr_ne(var, NULL);
  o_free(var);
  var = malloc(-1);
  ck_assert_ptr_eq(var, NULL);
}
END_TEST

START_TEST(test_o_realloc)
{
  void * var, * new_var;
  var = malloc(8);
  ck_assert_ptr_ne(var, NULL);
  var = realloc(var, 16);
  ck_assert_ptr_ne(var, NULL);
  new_var = realloc(var, -1);
  ck_assert_ptr_eq(new_var, NULL);
  o_free(var);
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests memory functions");
	tc_core = tcase_create("test_orcania_memory");
	tcase_add_test(tc_core, test_o_malloc);
	tcase_add_test(tc_core, test_o_realloc);
	tcase_set_timeout(tc_core, 30);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = orcania_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
