/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 */

#ifndef __ORCANIA_H__
#define __ORCANIA_H__

#ifndef U_DISABLE_JANSSON
#include <jansson.h>
#endif

#define ORCANIA_VERSION 1.2.4
/**
 * char * str_replace(const char * source, char * old, char * new)
 * replace all occurences of old by new in the string source
 * return a char * with the new value
 * return NULL on error
 * returned value must be free'd after use
 */
char * str_replace(const char * source, const char * str_old, const char * str_new);

/**
 * o_strdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strdup(const char * source);

/**
 * o_strndup
 * a modified strndup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strndup(const char * source, size_t len);

/**
 * o_strcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcmp(const char * p1, const char * p2);

/**
 * o_strncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncmp(const char * p1, const char * p2, size_t n);

/**
 * o_strcpy
 * a modified strcpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strcpy(char * p1, const char * p2);

/**
 * o_strncpy
 * a modified strncpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strncpy(char * p1, const char * p2, size_t n);

/**
 * o_strcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcasecmp(const char * p1, const char * p2);

/**
 * o_strncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncasecmp(const char * p1, const char * p2, size_t n);

/**
 * o_strstr
 * a modified strstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strstr(const char * haystack, const char * needle);

/**
 * o_strnstr
 * a modified strnstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strnstr(const char * haystack, const char * needle, size_t len);

/**
 * o_strcasestr
 * a modified strcasestr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strcasestr(const char * haystack, const char * needle);

/**
 * o_strchr
 * a modified strchr function that don't crash when haystack is NULL
 */
char * o_strchr(const char * haystack, int c);

/**
 * o_strrchr
 * a modified strrchr function that don't crash when haystack is NULL
 */
char * o_strrchr(const char * haystack, int c);

/**
 * o_strlen
 * a modified version of strlen that don't crash when s is NULL
 */
size_t o_strlen(const char * s);

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 */
char * msprintf(const char * message, ...);

/**
 * Split a string into an array of strings using separator string
 * return the number of elements to be returned, 0 on error
 * if return_array is not NULL, set the returned array in it
 * return_array is an array of char * ending with a NULL value
 * return_array must be free'd after use
 * you can use free_string_array to free return_array
 */
int split_string(const char * string, const char * separator, char *** return_array);

/**
 * Clean an array of strings
 */
void free_string_array(char ** array);

/**
 * Check if an array of string has a specified value, case sensitive
 */
int string_array_has_value(const char ** array, const char * needle);

/**
 * Check if an array of string has a specified value, case insensitive
 */
int string_array_has_value_case(const char ** array, const char * needle);

/**
 * Check if an array of string has a specified value, case sensitive, limit to len characters
 */
int string_array_has_value_n(const char ** array, const char * needle, size_t len);

/**
 * Check if an array of string has a specified value, case insensitive, limit to len characters
 */
int string_array_has_value_ncase(const char ** array, const char * needle, size_t len);

/**
 * Check if an array of string has a specified trimmed value
 */
int string_array_has_trimmed_value(const char ** array, const char * needle);

/**
 * Remove string of beginning and ending whitespaces
 */
char * trimwhitespace(char * str);

#ifndef U_DISABLE_JANSSON
/**
 * json_t * json_search(json_t * haystack, json_t * needle)
 * jansson library addon
 * This function could be removed if y pull request is accepted in jansson official repository:
 * https://github.com/akheron/jansson/pull/265
 * Look for an occurence of needle within haystack
 * If needle is present in haystack, return the reference to the json_t * that is equal to needle
 * If needle is not found, return NULL
 */
json_t * json_search(json_t * haystack, json_t * needle);

/**
 * Check if the result json object has a "result" element that is equal to value
 */
int check_result_value(json_t * result, const int value);
#endif

/**
 * Memory functions
 */
/* C89 allows these to be macros */
#undef malloc
#undef realloc
#undef free

typedef void *(*o_malloc_t)(size_t);
typedef void *(*o_realloc_t)(void *, size_t);
typedef void (*o_free_t)(void *);

void * o_malloc(size_t size);
void * o_realloc(void * ptr, size_t size);
void o_free(void * ptr);
void o_set_alloc_funcs(o_malloc_t malloc_fn, o_realloc_t realloc_fn, o_free_t free_fn);
void o_get_alloc_funcs(o_malloc_t * malloc_fn, o_realloc_t * realloc_fn, o_free_t * free_fn);

/**
 * Base64 encode and decode functions
 */

/**
 * o_base64_encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64_decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

#endif
