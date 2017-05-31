/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "../src/orcania.h"

START_TEST(test_str_replace)
{
  char * str = "abcdeffedcba", * old_1 = "cd", * new_1 = "gh", * old_2 = "f", * target;
  target = str_replace(str, old_1, new_1);
  ck_assert_str_eq(target, "abgheffedcba");
  ck_assert_ptr_eq(str_replace(NULL, old_1, new_1), NULL);
  ck_assert_ptr_eq(str_replace(str, NULL, new_1), NULL);
  ck_assert_ptr_eq(str_replace(str, old_1, NULL), NULL);
  o_free(target);
  target = str_replace(str, old_2, new_1);
  ck_assert_str_eq(target, "abcdeghghedcba");
  o_free(target);
  target = str_replace(str, str, "");
  ck_assert_str_eq(target, "");
  o_free(target);
}
END_TEST

START_TEST(test_o_strdup)
{
  char * str = "abcdeffedcba", * target;
  target = o_strdup(str);
  ck_assert_str_eq(target, str);
  o_free(target);
  ck_assert_ptr_eq(o_strdup(NULL), NULL);
}
END_TEST

START_TEST(test_o_strndup)
{
  char * str = "abcdeffedcba", * target;
  target = o_strndup(str, strlen(str));
  ck_assert_str_eq(target, str);
  o_free(target);
  target = o_strndup(str, strlen(str)-2);
  ck_assert_str_eq(target, "abcdeffedc");
  o_free(target);
  ck_assert_ptr_eq(o_strndup(NULL, 12), NULL);
  target = o_strndup("abcdeffedc", 0);
  ck_assert_ptr_ne(target, NULL);
  o_free(target);
}
END_TEST

START_TEST(test_o_strcmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "bob", * str_3 = "abcdeffedcba";
  ck_assert_int_eq(o_strcmp(str_1, str_3), 0);
  ck_assert_int_ne(o_strcmp(str_1, str_2), 0);
  ck_assert_int_ne(o_strcmp(str_1, NULL), 0);
  ck_assert_int_ne(o_strcmp(NULL, str_1), 0);
  ck_assert_int_eq(o_strcmp(NULL, NULL), 0);
}
END_TEST

START_TEST(test_o_strncmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "abc", * str_3 = "abcdeffedcba";
  ck_assert_int_eq(o_strncmp(str_1, str_3, strlen(str_3)), 0);
  ck_assert_int_eq(o_strncmp(str_1, str_2, strlen(str_2)), 0);
  ck_assert_int_ne(o_strncmp(str_1, str_2, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(str_1, NULL, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(NULL, str_1, strlen(str_1)), 0);
  ck_assert_int_eq(o_strncmp(NULL, NULL, 0), 0);
  ck_assert_int_eq(o_strncmp(NULL, NULL, 1), 0);
}
END_TEST

START_TEST(test_o_strcasecmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "bob", * str_3 = "AbcdeFfedcba";
  ck_assert_int_eq(o_strcasecmp(str_1, str_3), 0);
  ck_assert_int_ne(o_strcasecmp(str_1, str_2), 0);
  ck_assert_int_ne(o_strcasecmp(str_1, NULL), 0);
  ck_assert_int_ne(o_strcasecmp(NULL, str_1), 0);
  ck_assert_int_eq(o_strcasecmp(NULL, NULL), 0);
}
END_TEST

START_TEST(test_o_strncasecmp)
{
  char * str_1 = "abcdeFfedcba", * str_2 = "abC", * str_3 = "abCdeffedCba";
  ck_assert_int_eq(o_strncasecmp(str_1, str_3, strlen(str_3)), 0);
  ck_assert_int_eq(o_strncasecmp(str_1, str_2, strlen(str_2)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, str_2, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, NULL, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(NULL, str_1, strlen(str_1)), 0);
  ck_assert_int_eq(o_strncasecmp(NULL, NULL, 0), 0);
  ck_assert_int_eq(o_strncasecmp(NULL, NULL, 1), 0);
}
END_TEST

START_TEST(test_o_strcpy)
{
  char * src = "abcd", target[5];
  ck_assert_ptr_ne(o_strcpy(target, src), NULL);
  ck_assert_str_eq(target, src);
  ck_assert_ptr_eq(o_strcpy(target, NULL), NULL);
  ck_assert_ptr_eq(o_strcpy(NULL, src), NULL);
  ck_assert_ptr_eq(o_strcpy(NULL, NULL), NULL);
}
END_TEST

START_TEST(test_o_strncpy)
{
  char * src = "abcd", target[5] = {0};
  ck_assert_ptr_ne(o_strncpy(target, src, 3), NULL);
  ck_assert_str_eq(target, "abc");
  ck_assert_ptr_eq(o_strncpy(target, NULL, 4), NULL);
  ck_assert_ptr_eq(o_strncpy(NULL, src, 4), NULL);
  ck_assert_ptr_eq(o_strncpy(NULL, NULL, 4), NULL);
}
END_TEST

START_TEST(test_o_strstr)
{
  char * str_1 = "abcdeffedcba", * str_2 = "def", * str_3 = "bob";
  ck_assert_ptr_ne(o_strstr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strstr(str_1, str_3), NULL);
  ck_assert_ptr_eq(o_strstr(NULL, str_3), NULL);
  ck_assert_ptr_eq(o_strstr(str_1, NULL), NULL);
  ck_assert_ptr_eq(o_strstr(NULL, NULL), NULL);
}
END_TEST

START_TEST(test_o_strnstr)
{
  char * str_1 = "abcdeffedcba", * str_2 = "def", * str_3 = "bob";
  ck_assert_ptr_ne(o_strnstr(str_1, str_2, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, 0), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, str_3, strlen(str_3)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, NULL, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, NULL, strlen(str_3)), NULL);
}
END_TEST

START_TEST(test_o_strchr)
{
  char * str_1 = "abcdef", str_2 = 'd', str_3 = 'g';
  ck_assert_ptr_ne(o_strchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strchr(str_1, str_3), NULL);
  ck_assert_ptr_eq(o_strchr(NULL, str_3), NULL);
}
END_TEST

START_TEST(test_o_strrchr)
{
  char * str_1 = "abcdef", str_2 = 'd', str_3 = 'g';
  ck_assert_ptr_ne(o_strrchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strrchr(str_1, str_3), NULL);
  ck_assert_ptr_ne(o_strrchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strrchr(NULL, str_3), NULL);
}
END_TEST

START_TEST(test_o_strlen)
{
  ck_assert_int_eq(o_strlen("abcdef"), 6);
  ck_assert_int_eq(o_strlen(NULL), 0);
  ck_assert_int_eq(o_strlen(""), 0);
}
END_TEST

START_TEST(test_msprintf)
{
  char * target;
  target = msprintf("target1 %s %d %p", "str1", 42, NULL);
  ck_assert_str_eq(target, "target1 str1 42 (nil)");
  o_free(target);
  ck_assert_ptr_eq(msprintf(NULL, "str1", 42, NULL), NULL);
}
END_TEST

START_TEST(test_trimwhitespace)
{
  char * test1 = o_strdup(" bob trimmed  "), * test2 = o_strdup(" \t \t"), * test3 = o_strdup("");
  ck_assert_str_eq(trimwhitespace(test1), "bob trimmed");
  ck_assert_str_eq(trimwhitespace(test2), "");
  ck_assert_str_eq(trimwhitespace(test3), "");
  ck_assert_ptr_eq(trimwhitespace(NULL), NULL);
  o_free(test1);
  o_free(test2);
  o_free(test3);
}
END_TEST

START_TEST(test_base64)
{
  char * src = "source string", encoded[128], decoded[128];
  size_t encoded_size, decoded_size;
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_str_eq(encoded, "c291cmNlIHN0cmluZw==");
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_str_eq(decoded, src);
  ck_assert_int_eq(decoded_size, strlen(src));
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests string functions");
	tc_core = tcase_create("test_orcania_str");
	tcase_add_test(tc_core, test_str_replace);
	tcase_add_test(tc_core, test_o_strdup);
	tcase_add_test(tc_core, test_o_strndup);
	tcase_add_test(tc_core, test_o_strcmp);
	tcase_add_test(tc_core, test_o_strncmp);
	tcase_add_test(tc_core, test_o_strcasecmp);
	tcase_add_test(tc_core, test_o_strncasecmp);
	tcase_add_test(tc_core, test_o_strcpy);
	tcase_add_test(tc_core, test_o_strncpy);
	tcase_add_test(tc_core, test_o_strstr);
	tcase_add_test(tc_core, test_o_strnstr);
	tcase_add_test(tc_core, test_o_strchr);
	tcase_add_test(tc_core, test_o_strrchr);
	tcase_add_test(tc_core, test_o_strlen);
	tcase_add_test(tc_core, test_msprintf);
	tcase_add_test(tc_core, test_trimwhitespace);
	tcase_add_test(tc_core, test_base64);
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
