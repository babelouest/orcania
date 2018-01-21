/* Public domain, no copyright. Use at your own risk. */

#include <stdlib.h>
#include <string.h>

#include <check.h>
#include <orcania.h>

START_TEST(test_split_string)
{
  char * str = "ab,cd,ef,gghhii,jkl", * separator = ",", ** splitted;
  int nb_elt;
  nb_elt = split_string(str, separator, &splitted);
  ck_assert_ptr_ne(splitted, NULL);
  ck_assert_int_eq(nb_elt, 5);
  ck_assert_int_eq(split_string(str, "nope", NULL), 1);
  ck_assert_str_eq(splitted[0], "ab");
  free_string_array(splitted);
}
END_TEST

START_TEST(test_string_array_has_value)
{
  char * str = "ab,cd,ef,gghhii,jkl", * separator = ",", ** splitted;
  ck_assert_int_eq(split_string(str, separator, &splitted), 5);
  ck_assert_int_eq(string_array_has_value((const char **)splitted, "ab"), 1);
  ck_assert_int_eq(string_array_has_value((const char **)splitted, "nope"), 0);
  ck_assert_int_eq(string_array_has_value((const char **)splitted, NULL), 0);
  ck_assert_int_eq(string_array_has_value(NULL, "ab"), 0);
  free_string_array(splitted);
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests split string functions");
	tc_core = tcase_create("test_orcania_split");
	tcase_add_test(tc_core, test_split_string);
	tcase_add_test(tc_core, test_string_array_has_value);
	tcase_set_timeout(tc_core, 30);
	suite_add_tcase(s, tc_core);

	return s;
}

int main()
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
