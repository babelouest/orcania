/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "orcania.h"

static void run_test_base64(const unsigned char * src, size_t src_len, const unsigned char * b64_expected, size_t b64_expected_len, const unsigned char * b64url_expected, size_t b64url_expected_len) {
  unsigned char out[256] = {0}, * out_m;
  size_t out_len = 0;

  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64_encode(src, src_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, b64_expected_len);
  ck_assert_str_eq((const char *)out, (const char *)b64_expected);

  out_len = 0;
  ck_assert_int_eq(o_base64_encode(src, src_len, NULL, &out_len), 1);
  ck_assert_int_eq(out_len, b64_expected_len);
  out_m = o_malloc(out_len);
  out_len = 0;
  ck_assert_int_eq(o_base64_encode(src, src_len, out_m, &out_len), 1);
  o_free(out_m);

  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64_decode(b64_expected, b64_expected_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, src_len);
  ck_assert_int_eq(0, memcmp(src, out, out_len));

  out_len = 0;
  ck_assert_int_eq(o_base64_decode(b64_expected, b64_expected_len, NULL, &out_len), 1);
  ck_assert_int_eq(out_len, src_len);
  out_m = o_malloc(out_len+2);
  out_len = 0;
  ck_assert_int_eq(o_base64_decode(b64_expected, b64_expected_len, out_m, &out_len), 1);
  o_free(out_m);

  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64url_encode(src, src_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, b64url_expected_len);
  ck_assert_str_eq((const char *)out, (const char *)b64url_expected);

  out_len = 0;
  ck_assert_int_eq(o_base64url_encode(src, src_len, NULL, &out_len), 1);
  ck_assert_int_eq(out_len, b64url_expected_len);
  out_m = o_malloc(out_len);
  out_len = 0;
  ck_assert_int_eq(o_base64url_encode(src, src_len, out_m, &out_len), 1);
  o_free(out_m);

  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64url_decode(b64url_expected, b64url_expected_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, src_len);
  ck_assert_int_eq(0, memcmp(src, out, out_len));

  out_len = 0;
  ck_assert_int_eq(o_base64url_decode(b64url_expected, b64url_expected_len, NULL, &out_len), 1);
  ck_assert_int_eq(out_len, src_len);
  out_m = o_malloc(out_len+2);
  out_len = 0;
  ck_assert_int_eq(o_base64url_decode(b64url_expected, b64url_expected_len, out_m, &out_len), 1);
  o_free(out_m);

  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64_2_base64url(b64_expected, b64_expected_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, b64url_expected_len);
  ck_assert_int_eq(0, memcmp(b64url_expected, out, out_len));
  
  memset(out, 0, 256);
  out_len = 0;
  ck_assert_int_eq(o_base64url_2_base64(b64url_expected, b64url_expected_len, out, &out_len), 1);
  ck_assert_int_eq(out_len, b64_expected_len);
  ck_assert_int_eq(0, memcmp(b64_expected, out, out_len));
}

static void run_test_base64_alloc(const unsigned char * src, size_t src_len, const unsigned char * b64_expected, size_t b64_expected_len, const unsigned char * b64url_expected, size_t b64url_expected_len) {
  struct _o_datum dat = {0, NULL};

  ck_assert_int_eq(o_base64_encode_alloc(src, src_len, &dat), 1);
  ck_assert_int_eq(b64_expected_len, dat.size);
  ck_assert_str_eq((const char *)dat.data, (const char *)b64_expected);
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;

  ck_assert_int_eq(o_base64_decode_alloc(b64_expected, b64_expected_len, &dat), 1);
  ck_assert_int_eq(dat.size, src_len);
  ck_assert_int_eq(0, memcmp(src, dat.data, dat.size));
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;

  ck_assert_int_eq(o_base64url_encode_alloc(src, src_len, &dat), 1);
  ck_assert_int_eq(dat.size, b64url_expected_len);
  ck_assert_str_eq((const char *)dat.data, (const char *)b64url_expected);
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;

  ck_assert_int_eq(o_base64url_decode_alloc(b64url_expected, b64url_expected_len, &dat), 1);
  ck_assert_int_eq(dat.size, src_len);
  ck_assert_int_eq(0, memcmp(src, dat.data, dat.size));
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;

  ck_assert_int_eq(o_base64_2_base64url_alloc(b64_expected, b64_expected_len, &dat), 1);
  ck_assert_int_eq(dat.size, b64url_expected_len);
  ck_assert_int_eq(0, memcmp(b64url_expected, dat.data, dat.size));
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;
  
  ck_assert_int_eq(o_base64url_2_base64_alloc(b64url_expected, b64url_expected_len, &dat), 1);
  ck_assert_int_eq(dat.size, b64_expected_len);
  ck_assert_int_eq(0, memcmp(b64_expected, dat.data, dat.size));
  o_free(dat.data);
  dat.data = NULL;
  dat.size = 0;
}

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
  target = o_strndup(str, o_strlen(str));
  ck_assert_str_eq(target, str);
  o_free(target);
  target = o_strndup(str, o_strlen(str)-2);
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
  ck_assert_int_eq(o_strncmp(str_1, str_3, o_strlen(str_3)), 0);
  ck_assert_int_eq(o_strncmp(str_1, str_2, o_strlen(str_2)), 0);
  ck_assert_int_ne(o_strncmp(str_1, str_2, o_strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(str_1, NULL, o_strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(NULL, str_1, o_strlen(str_1)), 0);
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
  ck_assert_int_eq(o_strncasecmp(str_1, str_3, o_strlen(str_3)), 0);
  ck_assert_int_eq(o_strncasecmp(str_1, str_2, o_strlen(str_2)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, str_2, o_strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, NULL, o_strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(NULL, str_1, o_strlen(str_1)), 0);
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
  ck_assert_ptr_ne(o_strnstr(str_1, str_2, o_strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, o_strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, 0), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, str_3, o_strlen(str_3)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, NULL, o_strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, NULL, o_strlen(str_3)), NULL);
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

START_TEST(test_o_strnchr)
{
  char * str_1 = "abcdef", str_2 = 'd';
  ck_assert_ptr_ne(o_strnchr(str_1, 5, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(str_1, 2, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(str_1, 0, str_2), NULL);
  ck_assert_ptr_ne(o_strnchr(str_1, 8, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(NULL, 4, str_2), NULL);
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

START_TEST(test_o_strrnchr)
{
  char * str_1 = "abcdef", str_2 = 'd';
  ck_assert_ptr_ne(o_strrnchr(str_1, 5, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(str_1, 2, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(str_1, 0, str_2), NULL);
  ck_assert_ptr_ne(o_strrnchr(str_1, 8, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(NULL, 4, str_2), NULL);
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
  char tmp[100];
  target = msprintf("target1 %s %d %s %p", "str1", 42, "pl\342\230\272op", NULL);
  sprintf(tmp, "target1 %s %d %s %p", "str1", 42, "pl\342\230\272op", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  ck_assert_ptr_eq(msprintf(NULL, "str1", 42, "pl\342\230\272op", NULL), NULL);
  target = msprintf("");
  ck_assert_ptr_ne(NULL, target);
  o_free(target);
}
END_TEST

START_TEST(test_mstrcatf)
{
  char * target;
  char tmp[200];
  target = msprintf("target1 %s %d %s %p", "str1", 42, "pl\342\230\272op", NULL);
  target = mstrcatf(target, "target2 %s %d %p", "str2", 42, NULL);
  sprintf(tmp, "target1 str1 42 %s %ptarget2 %s 42 %p", "pl\342\230\272op", NULL, "str2", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  ck_assert_ptr_eq(msprintf(NULL, NULL, "str1", 42, NULL), NULL);
  target = NULL;
  target = mstrcatf(target, "target2 %s %d %s %p", "str2", 42, "pl\342\230\272op", NULL);
  sprintf(tmp, "target2 %s 42 %s %p", "str2", "pl\342\230\272op", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  target = msprintf("target1 %s %d %s %p", "str1", 42, "pl\342\230\272op", NULL);
  target = mstrcatf(target, "");
  sprintf(tmp, "target1 str1 42 %s %p", "pl\342\230\272op", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  target = mstrcatf(NULL, "%s", "plop");
  ck_assert_ptr_ne(NULL, target);
  ck_assert_str_eq("plop", target);
  o_free(target);
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

START_TEST(test_trimcharacter)
{
  char test1[] = "3bob trimmed33", test2[] = "333", test3[] = "";
  ck_assert_str_eq(trimcharacter(test1, '3'), "bob trimmed");
  ck_assert_str_eq(trimcharacter(test2, '3'), "");
  ck_assert_str_eq(trimcharacter(test3, '3'), "");
  ck_assert_ptr_eq(trimcharacter(NULL, '3'), NULL);
}
END_TEST

START_TEST(test_split_string)
{
  char ** array;
  
  ck_assert_int_eq(split_string("Alice,Bob,Carol,Dave,Eve,Isaac", ",", &array), 6);
	free_string_array(array);
  array = NULL;
  
  ck_assert_int_eq(split_string("Alice,Bob,Carol,Dave,Eve,Isaac", " ", &array), 1);
	free_string_array(array);
  array = NULL;
  
  ck_assert_int_eq(split_string("Alice,Bob,Carol,Dave,Eve,Isaac", ",D", &array), 2);
	free_string_array(array);
  array = NULL;
  
  ck_assert_int_eq(split_string("Alice,Bob,Carol,Dave,Eve,Isaac", ",g", &array), 1);
	free_string_array(array);
  array = NULL;
  
  ck_assert_int_eq(split_string("", ",", &array), 1);
	free_string_array(array);
  array = NULL;
  
  ck_assert_int_eq(split_string(NULL, ",", &array), 0);
}
END_TEST

START_TEST(test_string_array)
{
	char ** array, * str_orig = "Alice,Bob,Carol,Dave,Eve,Isaac";
	int size = split_string(str_orig, ",", &array);
	
	ck_assert_int_eq(size, 6);
	ck_assert_int_eq(string_array_has_value((const char **)array, "Alice"), 1);
	ck_assert_int_eq(string_array_has_value((const char **)array, "Ali"), 0);
	ck_assert_int_eq(string_array_has_value((const char **)array, "Mallory"), 0);
	ck_assert_int_eq(string_array_has_value_case((const char **)array, "alice"), 1);
	ck_assert_int_eq(string_array_has_value_case((const char **)array, "ali"), 0);
	ck_assert_int_eq(string_array_has_value_case((const char **)array, "mallory"), 0);
	ck_assert_int_eq(string_array_has_value_n((const char **)array, "Ali", 3), 1);
	ck_assert_int_eq(string_array_has_value_n((const char **)array, "Aliceeee", 5), 1);
	ck_assert_int_eq(string_array_has_value_n((const char **)array, "Malloryyyy", 7), 0);
	ck_assert_int_eq(string_array_has_value_ncase((const char **)array, "aliceeee", 5), 1);
	ck_assert_int_eq(string_array_has_value_ncase((const char **)array, "malloryyyy", 7), 0);
	
	free_string_array(array);
}
END_TEST

START_TEST(test_string_array_has_trimmed_value)
{
	char ** array, * str_orig = "Alice,Bob,Carol,Dave,Eve,Isaac", * str_match_ok = "Carol", * str_match_not_found = "Sam";
	int size = split_string(str_orig, ",", &array);
	
	ck_assert_int_eq(size, 6);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, str_match_ok), 1);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, str_match_not_found), 0);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, NULL), 0);
	ck_assert_int_eq(string_array_has_trimmed_value(NULL, str_match_ok), 0);
	ck_assert_int_eq(string_array_has_trimmed_value(NULL, NULL), 0);
	
	free_string_array(array);
}
END_TEST

START_TEST(test_base64)
{
  char * src = "source string", encoded[128] = {0}, decoded[128] = {0}, b64_error[] = ";error;", b64_error_2[] = "c291cmNlIHN0cmluZw==";
  size_t encoded_size, decoded_size, b64_error_2_len = 20;
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_str_eq(encoded, "c291cmNlIHN0cmluZw==");
  ck_assert_int_eq(20, encoded_size);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size-1, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size-2, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size-3, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size-4, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)(encoded+1), encoded_size-1, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)(encoded+2), encoded_size-2, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)(encoded+3), encoded_size-3, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"", 0, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"Zw==", 4, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"Z===", 4, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"==", 2, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"===", 3, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"====", 4, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZw==", 8, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZwe=", 8, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZweS", 8, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZ ==", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZ===", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmlu=  =", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmlu====", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)" cmlu===", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmlu==E=", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)"cmluZ=eS", 8, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_str_eq(decoded, src);
  ck_assert_int_eq(decoded_size, o_strlen(src));
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error, o_strlen(b64_error), NULL, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error, o_strlen(b64_error), (unsigned char *)decoded, &decoded_size), 0);
  
  memset(encoded, 0, 128);
  memset(decoded, 0, 128);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, 1, (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(4, encoded_size);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, 3, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, 2, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, 1, (unsigned char *)decoded, &decoded_size), 0);

  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 1);
  // Insert invalid characters
  b64_error_2[4] = 0;
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 2;
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 11;
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 128;
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = '=';
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_gt(o_strlen(src), decoded_size);
  b64_error_2[4] = '-';
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = '_';
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
}
END_TEST

START_TEST(test_base64_more_test_cases)
{
  const unsigned char message1[] = "C combines the power and performance of assembly language with the flexibility and ease-of-use of assembly language.",
                      message2[] = "Bryan is in\nthe kitchen",
                      message3[] = {0},
                      message4[] = {0, 0},
                      message5[] = {0, 0, 0},
                      message6[] = {0x32, 0x0, 0x0},
                      message7[] = "아쿠아 포니",
                      message8[] = {0x76, 0x65, 0x72, 0x79, 0x00, 0x20, 0x75, 0x6e, 0x75, 0x73, 0x75, 0x61, 0x6c, 0x9b, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67},
                      message9[] = "\377",
                      message10[] = "\377\377",
                      message11[] = "\377\377\377",
                      message12[] = "\xff\xef";
  const unsigned char message1_b64[] = "QyBjb21iaW5lcyB0aGUgcG93ZXIgYW5kIHBlcmZvcm1hbmNlIG9mIGFzc2VtYmx5IGxhbmd1YWdlIHdpdGggdGhlIGZsZXhpYmlsaXR5IGFuZCBlYXNlLW9mLXVzZSBvZiBhc3NlbWJseSBsYW5ndWFnZS4=",
                      message2_b64[] = "QnJ5YW4gaXMgaW4KdGhlIGtpdGNoZW4=",
                      message3_b64[] = "AA==",
                      message4_b64[] = "AAA=",
                      message5_b64[] = "AAAA",
                      message6_b64[] = "MgAA",
                      message7_b64[] = "7JWE7L+g7JWEIO2PrOuLiAA=",
                      message8_b64[] = "dmVyeQAgdW51c3VhbJsgc3RyaW5n",
                      message9_b64[] = "/w==",
                      message10_b64[] = "//8=",
                      message11_b64[] = "////",
                      message12_b64[] = "/+8=";
  const unsigned char message1_b64url[] = "QyBjb21iaW5lcyB0aGUgcG93ZXIgYW5kIHBlcmZvcm1hbmNlIG9mIGFzc2VtYmx5IGxhbmd1YWdlIHdpdGggdGhlIGZsZXhpYmlsaXR5IGFuZCBlYXNlLW9mLXVzZSBvZiBhc3NlbWJseSBsYW5ndWFnZS4",
                      message2_b64url[] = "QnJ5YW4gaXMgaW4KdGhlIGtpdGNoZW4",
                      message3_b64url[] = "AA",
                      message4_b64url[] = "AAA",
                      message5_b64url[] = "AAAA",
                      message6_b64url[] = "MgAA",
                      message7_b64url[] = "7JWE7L-g7JWEIO2PrOuLiAA",
                      message8_b64url[] = "dmVyeQAgdW51c3VhbJsgc3RyaW5n",
                      message9_b64url[] = "_w",
                      message10_b64url[] = "__8",
                      message11_b64url[] = "____",
                      message12_b64url[] = "_-8";
  
  run_test_base64(message1, o_strlen((const char *)message1), message1_b64, o_strlen((const char *)message1_b64), message1_b64url, o_strlen((const char *)message1_b64url));
  run_test_base64(message2, o_strlen((const char *)message2), message2_b64, o_strlen((const char *)message2_b64), message2_b64url, o_strlen((const char *)message2_b64url));
  run_test_base64(message3, sizeof(message3), message3_b64, o_strlen((const char *)message3_b64), message3_b64url, o_strlen((const char *)message3_b64url));
  run_test_base64(message4, sizeof(message4), message4_b64, o_strlen((const char *)message4_b64), message4_b64url, o_strlen((const char *)message4_b64url));
  run_test_base64(message5, sizeof(message5), message5_b64, o_strlen((const char *)message5_b64), message5_b64url, o_strlen((const char *)message5_b64url));
  run_test_base64(message6, sizeof(message6), message6_b64, o_strlen((const char *)message6_b64), message6_b64url, o_strlen((const char *)message6_b64url));
  run_test_base64(message7, sizeof(message7), message7_b64, o_strlen((const char *)message7_b64), message7_b64url, o_strlen((const char *)message7_b64url));
  run_test_base64(message8, sizeof(message8), message8_b64, o_strlen((const char *)message8_b64), message8_b64url, o_strlen((const char *)message8_b64url));
  run_test_base64(message9, o_strlen((const char *)message9), message9_b64, o_strlen((const char *)message9_b64), message9_b64url, o_strlen((const char *)message9_b64url));
  run_test_base64(message10, o_strlen((const char *)message10), message10_b64, o_strlen((const char *)message10_b64), message10_b64url, o_strlen((const char *)message10_b64url));
  run_test_base64(message11, o_strlen((const char *)message11), message11_b64, o_strlen((const char *)message11_b64), message11_b64url, o_strlen((const char *)message11_b64url));
  run_test_base64(message12, o_strlen((const char *)message12), message12_b64, o_strlen((const char *)message12_b64), message12_b64url, o_strlen((const char *)message12_b64url));
}
END_TEST

START_TEST(test_base64url)
{
  char * src = "source string", encoded[128] = {0}, decoded[128] = {0}, b64_error[] = ";error;", b64_error_2[] = "c291cmNlIHN0cmluZw";
  size_t encoded_size, decoded_size, b64_error_2_len = 18;
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_str_eq(encoded, "c291cmNlIHN0cmluZw");
  ck_assert_int_eq(18, encoded_size);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size-1, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size-2, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size-3, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size-4, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)(encoded+1), encoded_size-1, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"", 0, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"Zw", 2, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"Zw  ", 4, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"Z   ", 4, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"    ", 4, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmluZw  ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmluZwe ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmluZweS", 8, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmluZ   ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"  cmluZ ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmlu    ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)" cmlu   ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)"cmlu  E ", 8, (unsigned char *)decoded, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_str_eq(decoded, src);
  ck_assert_int_eq(decoded_size, o_strlen(src));
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error, o_strlen(b64_error), NULL, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error, o_strlen(b64_error), (unsigned char *)decoded, &decoded_size), 0);

  memset(encoded, 0, 128);
  memset(decoded, 0, 128);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, 1, (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(2, encoded_size);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, 1, (unsigned char *)decoded, &decoded_size), 0);

  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 1);
  // Insert invalid characters
  b64_error_2[4] = 0;
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 2;
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 11;
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = 128;
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = '=';
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = '+';
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
  b64_error_2[4] = '/';
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error_2, b64_error_2_len, (unsigned char *)decoded, &decoded_size), 0);
}
END_TEST

START_TEST(test_base64url_2_base64)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0}, encoded[21] = {0}, encoded_url[21] = {0}, encoded_new[19] = {0};
  size_t encoded_size = 0, encoded_new_size = 0;
  ck_assert_int_eq(o_base64_encode(src, 10, encoded, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded[encoded_size] = '\0'; // should be "b1twKSctPUB+AA=="
  ck_assert_int_eq(o_base64url_encode(src, 10, encoded_url, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded_url[encoded_size] = '\0'; // should be "b1twKSctPUB-AA"
  ck_assert_str_ne((const char *)encoded_url, (const char *)encoded);
  ck_assert_int_eq(o_base64url_2_base64(encoded_url, encoded_size, encoded_new, &encoded_new_size), 1);
  encoded_new[encoded_new_size] = '\0';
  ck_assert_str_eq((const char *)encoded_new, (const char *)encoded);
}
END_TEST

START_TEST(test_base64_2_base64url)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0}, encoded[21] = {0}, encoded_url[21] = {0}, encoded_new[19] = {0};
  size_t encoded_size = 0, encoded_new_size = 0;
  ck_assert_int_eq(o_base64url_encode(src, 10, encoded, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded[encoded_size] = '\0'; // should be "b1twKSctPUB-AA"
  ck_assert_int_eq(o_base64_encode(src, 10, encoded_url, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded_url[encoded_size] = '\0'; // should be "b1twKSctPUB+AA=="
  ck_assert_str_ne((const char *)encoded_url, (const char *)encoded);
  ck_assert_int_eq(o_base64_2_base64url(encoded_url, encoded_size, encoded_new, &encoded_new_size), 1);
  encoded_new[encoded_new_size] = '\0';
  ck_assert_str_eq((const char *)encoded_new, (const char *)encoded);
}
END_TEST

START_TEST(test_base64_len)
{
  char * src1 = "a", * src2 = "aa", * src3 = "aaa", * src4 = "aaaa", * src5 = "aaaaa", * src = "source string", encoded[128] = {0};
  char * src1_enc = "YQ==", * src2_enc = "YWE=", * src3_enc = "YWFh", *src4_enc = "YWFhYQ==", *src5_enc = "YWFhYWE=";
  size_t encoded_size, decoded_size;
  
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 20);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, NULL, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 13);
  
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 18);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size, NULL, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 13);

  ck_assert_int_eq(o_base64_encode((unsigned char *)src1, o_strlen(src1), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src2, o_strlen(src2), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src3, o_strlen(src3), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src4, o_strlen(src4), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 8);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src5, o_strlen(src5), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 8);
  
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src1, o_strlen(src1), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src2, o_strlen(src2), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src3, o_strlen(src3), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src4, o_strlen(src4), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 6);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src5, o_strlen(src5), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 7);
  
  ck_assert_int_eq(o_base64_decode((unsigned char *)src1_enc, o_strlen(src1_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src2_enc, o_strlen(src2_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src3_enc, o_strlen(src3_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src4_enc, o_strlen(src4_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src5_enc, o_strlen(src5_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 5);
  
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src1_enc, o_strlen(src1_enc)-2, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src2_enc, o_strlen(src2_enc)-1, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src3_enc, o_strlen(src3_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src4_enc, o_strlen(src4_enc)-2, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src5_enc, o_strlen(src5_enc)-1, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 5);
}
END_TEST

START_TEST(test_base64_alloc)
{
  char * src = "source string", b64_error[] = ";error;";
  struct _o_datum dat = {0, NULL}, dat_dec = {0, NULL};
  ck_assert_int_eq(o_base64_encode_alloc((unsigned char *)src, o_strlen(src), &dat), 1);
  ck_assert_int_eq(20, dat.size);
  ck_assert_int_eq(0, o_strncmp((const char *)dat.data, "c291cmNlIHN0cmluZw==", dat.size));
  ck_assert_int_eq(o_base64_decode_alloc(dat.data, dat.size, &dat_dec), 1);
  ck_assert_int_eq(dat_dec.size, o_strlen(src));
  ck_assert_int_eq(0, o_strncmp((const char *)dat_dec.data, src, dat_dec.size));
  ck_assert_int_eq(o_base64_decode_alloc((unsigned char *)b64_error, o_strlen(b64_error), &dat_dec), 0);
  o_free(dat.data);
  o_free(dat_dec.data);
}
END_TEST

START_TEST(test_base64url_alloc)
{
  char * src = "source string", b64_error[] = ";error;";
  struct _o_datum dat = {0, NULL}, dat_dec = {0, NULL};
  ck_assert_int_eq(o_base64url_encode_alloc((unsigned char *)src, o_strlen(src), &dat), 1);
  ck_assert_int_eq(18, dat.size);
  ck_assert_int_eq(0, o_strncmp((const char *)dat.data, "c291cmNlIHN0cmluZw", dat.size));
  ck_assert_int_eq(o_base64url_decode_alloc(dat.data, dat.size, &dat_dec), 1);
  ck_assert_int_eq(dat_dec.size, o_strlen(src));
  ck_assert_int_eq(0, o_strncmp((const char *)dat_dec.data, src, dat_dec.size));
  ck_assert_int_eq(o_base64url_decode_alloc((unsigned char *)b64_error, o_strlen(b64_error), &dat_dec), 0);
  o_free(dat.data);
  o_free(dat_dec.data);
}
END_TEST

START_TEST(test_base64_more_test_cases_alloc)
{
  const unsigned char message1[] = "C combines the power and performance of assembly language with the flexibility and ease-of-use of assembly language.",
                      message2[] = "Bryan is in\nthe kitchen",
                      message3[] = {0},
                      message4[] = {0, 0},
                      message5[] = {0, 0, 0},
                      message6[] = {0x32, 0x0, 0x0},
                      message7[] = "아쿠아 포니",
                      message8[] = {0x76, 0x65, 0x72, 0x79, 0x00, 0x20, 0x75, 0x6e, 0x75, 0x73, 0x75, 0x61, 0x6c, 0x9b, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67},
                      message9[] = "\377",
                      message10[] = "\377\377",
                      message11[] = "\377\377\377",
                      message12[] = "\xff\xef";
  const unsigned char message1_b64[] = "QyBjb21iaW5lcyB0aGUgcG93ZXIgYW5kIHBlcmZvcm1hbmNlIG9mIGFzc2VtYmx5IGxhbmd1YWdlIHdpdGggdGhlIGZsZXhpYmlsaXR5IGFuZCBlYXNlLW9mLXVzZSBvZiBhc3NlbWJseSBsYW5ndWFnZS4=",
                      message2_b64[] = "QnJ5YW4gaXMgaW4KdGhlIGtpdGNoZW4=",
                      message3_b64[] = "AA==",
                      message4_b64[] = "AAA=",
                      message5_b64[] = "AAAA",
                      message6_b64[] = "MgAA",
                      message7_b64[] = "7JWE7L+g7JWEIO2PrOuLiAA=",
                      message8_b64[] = "dmVyeQAgdW51c3VhbJsgc3RyaW5n",
                      message9_b64[] = "/w==",
                      message10_b64[] = "//8=",
                      message11_b64[] = "////",
                      message12_b64[] = "/+8=";
  const unsigned char message1_b64url[] = "QyBjb21iaW5lcyB0aGUgcG93ZXIgYW5kIHBlcmZvcm1hbmNlIG9mIGFzc2VtYmx5IGxhbmd1YWdlIHdpdGggdGhlIGZsZXhpYmlsaXR5IGFuZCBlYXNlLW9mLXVzZSBvZiBhc3NlbWJseSBsYW5ndWFnZS4",
                      message2_b64url[] = "QnJ5YW4gaXMgaW4KdGhlIGtpdGNoZW4",
                      message3_b64url[] = "AA",
                      message4_b64url[] = "AAA",
                      message5_b64url[] = "AAAA",
                      message6_b64url[] = "MgAA",
                      message7_b64url[] = "7JWE7L-g7JWEIO2PrOuLiAA",
                      message8_b64url[] = "dmVyeQAgdW51c3VhbJsgc3RyaW5n",
                      message9_b64url[] = "_w",
                      message10_b64url[] = "__8",
                      message11_b64url[] = "____",
                      message12_b64url[] = "_-8";
  
  run_test_base64_alloc(message1, o_strlen((const char *)message1), message1_b64, o_strlen((const char *)message1_b64), message1_b64url, o_strlen((const char *)message1_b64url));
  run_test_base64_alloc(message2, o_strlen((const char *)message2), message2_b64, o_strlen((const char *)message2_b64), message2_b64url, o_strlen((const char *)message2_b64url));
  run_test_base64_alloc(message3, sizeof(message3), message3_b64, o_strlen((const char *)message3_b64), message3_b64url, o_strlen((const char *)message3_b64url));
  run_test_base64_alloc(message4, sizeof(message4), message4_b64, o_strlen((const char *)message4_b64), message4_b64url, o_strlen((const char *)message4_b64url));
  run_test_base64_alloc(message5, sizeof(message5), message5_b64, o_strlen((const char *)message5_b64), message5_b64url, o_strlen((const char *)message5_b64url));
  run_test_base64_alloc(message6, sizeof(message6), message6_b64, o_strlen((const char *)message6_b64), message6_b64url, o_strlen((const char *)message6_b64url));
  run_test_base64_alloc(message7, sizeof(message7), message7_b64, o_strlen((const char *)message7_b64), message7_b64url, o_strlen((const char *)message7_b64url));
  run_test_base64_alloc(message8, sizeof(message8), message8_b64, o_strlen((const char *)message8_b64), message8_b64url, o_strlen((const char *)message8_b64url));
  run_test_base64_alloc(message9, o_strlen((const char *)message9), message9_b64, o_strlen((const char *)message9_b64), message9_b64url, o_strlen((const char *)message9_b64url));
  run_test_base64_alloc(message10, o_strlen((const char *)message10), message10_b64, o_strlen((const char *)message10_b64), message10_b64url, o_strlen((const char *)message10_b64url));
  run_test_base64_alloc(message11, o_strlen((const char *)message11), message11_b64, o_strlen((const char *)message11_b64), message11_b64url, o_strlen((const char *)message11_b64url));
  run_test_base64_alloc(message12, o_strlen((const char *)message12), message12_b64, o_strlen((const char *)message12_b64), message12_b64url, o_strlen((const char *)message12_b64url));
}
END_TEST

START_TEST(test_base64url_2_base64_alloc)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0};
  struct _o_datum dat = {0, NULL}, dat_url = {0, NULL}, dat_conv = {0, NULL};
  ck_assert_int_eq(o_base64_encode_alloc(src, 10, &dat), 1);
  ck_assert_int_gt(dat.size, 0);
  ck_assert_int_eq(o_base64url_encode_alloc(src, 10, &dat_url), 1);
  ck_assert_int_gt(dat_url.size, 0);
  ck_assert_int_ne(0, memcmp((const char *)dat.data, (const char *)dat_url.data, dat.size));
  ck_assert_int_eq(o_base64url_2_base64_alloc(dat_url.data, dat_url.size, &dat_conv), 1);
  ck_assert_int_eq(dat.size, dat_conv.size);
  ck_assert_int_eq(0, memcmp(dat_conv.data, dat.data, dat_conv.size));
  o_free(dat.data);
  o_free(dat_url.data);
  o_free(dat_conv.data);
}
END_TEST

START_TEST(test_base64_2_base64url_alloc)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0};
  struct _o_datum dat = {0, NULL}, dat_url = {0, NULL}, dat_conv = {0, NULL};
  ck_assert_int_eq(o_base64_encode_alloc(src, 10, &dat), 1);
  ck_assert_int_gt(dat.size, 0);
  ck_assert_int_eq(o_base64url_encode_alloc(src, 10, &dat_url), 1);
  ck_assert_int_gt(dat_url.size, 0);
  ck_assert_int_ne(0, memcmp((const char *)dat.data, (const char *)dat_url.data, dat.size));
  ck_assert_int_eq(o_base64_2_base64url_alloc(dat.data, dat.size, &dat_conv), 1);
  ck_assert_int_eq(dat_url.size, dat_conv.size);
  ck_assert_int_eq(0, memcmp(dat_conv.data, dat_url.data, dat_conv.size));
  o_free(dat.data);
  o_free(dat_url.data);
  o_free(dat_conv.data);
}
END_TEST

START_TEST(test_str_null_or_empty)
{
  char a[1] = {0}, * b = NULL, c[] = "test";
  
  ck_assert_int_eq(1, o_strnullempty(a));
  ck_assert_int_eq(1, o_strnullempty(b));
  ck_assert_int_eq(0, o_strnullempty(c));
  c[2] = '\0';
  ck_assert_int_eq(0, o_strnullempty(c));
  c[0] = '\0';
  ck_assert_int_eq(1, o_strnullempty(c));
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
	tcase_add_test(tc_core, test_o_strnchr);
	tcase_add_test(tc_core, test_o_strrchr);
	tcase_add_test(tc_core, test_o_strrnchr);
	tcase_add_test(tc_core, test_o_strlen);
	tcase_add_test(tc_core, test_msprintf);
	tcase_add_test(tc_core, test_mstrcatf);
	tcase_add_test(tc_core, test_trimwhitespace);
	tcase_add_test(tc_core, test_trimcharacter);
	tcase_add_test(tc_core, test_base64);
	tcase_add_test(tc_core, test_base64_more_test_cases);
	tcase_add_test(tc_core, test_base64url);
	tcase_add_test(tc_core, test_base64url_2_base64);
	tcase_add_test(tc_core, test_base64_2_base64url);
	tcase_add_test(tc_core, test_base64_len);
	tcase_add_test(tc_core, test_base64_alloc);
	tcase_add_test(tc_core, test_base64url_alloc);
	tcase_add_test(tc_core, test_base64_more_test_cases_alloc);
	tcase_add_test(tc_core, test_base64url_2_base64_alloc);
	tcase_add_test(tc_core, test_base64_2_base64url_alloc);
	tcase_add_test(tc_core, test_split_string);
	tcase_add_test(tc_core, test_string_array);
	tcase_add_test(tc_core, test_string_array_has_trimmed_value);
	tcase_add_test(tc_core, test_str_null_or_empty);
	tcase_set_timeout(tc_core, 30);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
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
