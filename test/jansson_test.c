/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include <jansson.h>
#include "../src/orcania.h"

START_TEST(test_json_search)
{
  json_t * haystack = json_pack("{sss{sssss{si}}}", "a", "b", "c", "d", "e", "f", "g", "h", "i", 42),
         * needle_found = json_string("e"),
         * needle_not_found = json_string("nope");
  ck_assert_ptr_ne(json_search(haystack, needle_found), NULL);
  ck_assert_ptr_eq(json_search(haystack, needle_not_found), NULL);
  ck_assert_ptr_eq(json_search(haystack, NULL), NULL);
  ck_assert_ptr_eq(json_search(NULL, needle_found), NULL);
  json_decref(haystack);
  json_decref(needle_found);
  json_decref(needle_not_found);
}
END_TEST

START_TEST(test_check_result_value)
{
  json_t * j_result = json_pack("{sis{sss{sssss{si}}}}", "result", 1, "value", "result", "b", "c", "d", "e", "f", "g", "h", "i", 42);
  ck_assert_int_eq(check_result_value(j_result, 1), 1);
  ck_assert_int_eq(check_result_value(j_result, 42), 0);
  ck_assert_int_eq(check_result_value(NULL, 1), 0);
  ck_assert_int_eq(check_result_value(json_object_get(j_result, "value"), 1), 0);
  ck_assert_int_eq(check_result_value(json_object_get(json_object_get(j_result, "value"), "h"), 1), 0);
  json_decref(j_result);
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests jansson functions");
	tc_core = tcase_create("test_orcania_jansson");
	tcase_add_test(tc_core, test_json_search);
	tcase_add_test(tc_core, test_check_result_value);
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
