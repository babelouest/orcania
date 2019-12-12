/**
 * 
 * @file orcania.h
 * @brief Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 * orcania.h: public header file
 * 
 * Copyright 2015-2018 Nicolas Mora <mail@babelouest.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU GENERAL PUBLIC LICENSE for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef __ORCANIA_H__
#define __ORCANIA_H__

#include "orcania-cfg.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @defgroup str string functions
 * @{
 */

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
 * Remove string of beginning and ending whitespaces
 */
char * trimwhitespace(char * str);

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 */
char * msprintf(const char * message, ...);

/**
 * char * mstrcatf((char * source, const char * message, ...)
 * A combination of strcat and msprintf that will concat source and message formatted
 * and return the combination as a new allocated char *
 * and will o_free source
 * but don't forget to free the returned value after use!
 */
char * mstrcatf(char * source, const char * message, ...);

/**
 * @}
 */

/**
 * @defgroup split split string and string array functions
 * @{
 */

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
 * Count the number of elements in an array of strings
 */
size_t string_array_size(char ** array);

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
 * Join a string array into a single string
 */
char * string_array_join(const char ** array, const char * separator);

/**
 * @}
 */

/**
 * @defgroup plist _pointer_list structure
 * @{
 */
struct _pointer_list {
  size_t size; /* size of the list */
  void ** list; /* list of pointers */
};

/**
 * pointer_list_init
 * Initialize a pointer list structure
 */
void pointer_list_init(struct _pointer_list * pointer_list);

/**
 * pointer_list_clean
 * Clean a pointer list structure
 */
void pointer_list_clean(struct _pointer_list * pointer_list);

/**
 * pointer_list_clean_free
 * Clean a pointer list structure
 * Free all elements using the free_function given in parameters
 */
void pointer_list_clean_free(struct _pointer_list * pointer_list, void (* free_function)(void * elt));

/**
 * pointer_list_size
 * Return the size of a pointer list
 */
size_t pointer_list_size(struct _pointer_list * pointer_list);

/**
 * pointer_list_append
 * Appends an element at the end of a pointer list
 * Return 1 on success, 0 on error
 */
int pointer_list_append(struct _pointer_list * pointer_list, void * element);

/**
 * pointer_list_get_at
 * Returns an element of a pointer list at the specified index or NULL if non valid index
 */
void * pointer_list_get_at(struct _pointer_list * pointer_list, size_t index);

/**
 * pointer_list_remove_at
 * Removes an element of a pointer list at the specified index
 * Return 1 on success, 0 on error or non valid index
 */
int pointer_list_remove_at(struct _pointer_list * pointer_list, size_t index);

/**
 * pointer_list_remove_at_free
 * Removes an element of a pointer list at the specified index
 * Return 1 on success, 0 on error or non valid index
 * Free the element using the free_function given in parameters
 */
int pointer_list_remove_at_free(struct _pointer_list * pointer_list, size_t index, void (* free_function)(void * elt));

/**
 * pointer_list_insert_at
 * Inserts an element at the specified index of a pointer list
 * Return 1 on success, 0 on error or non valid index
 */
int pointer_list_insert_at(struct _pointer_list * pointer_list, void * element, size_t index);

/**
 * pointer_list_remove_pointer
 * Removes an element of a pointer list corresponding to the specified element
 * Return 1 on success, 0 on error or non valid element
 */
int pointer_list_remove_pointer(struct _pointer_list * pointer_list, void * element);

/**
 * pointer_list_remove_pointer_free
 * Removes an element of a pointer list corresponding to the specified element
 * Free the element using the free_function given in parameters
 * Return 1 on success, 0 on error or non valid element
 */
int pointer_list_remove_pointer_free(struct _pointer_list * pointer_list, void * element, void (* free_function)(void * elt));

/**
 * @}
 */

/**
 * @defgroup mem Memory functions
 * @{
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
 * @}
 */

/**
 * @defgroup base64 Base64 encode and decode functions
 * @{
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

/**
 * o_base64url_encode - Base64url encode (url format)
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_decode - Base64 decode (url format)
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_2_base64 - Convert a base64 url format to base64 format
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64url_2_base64(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_2_base64 - Convert a base64 format to base64 url format
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64_2_base64url(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * @}
 */
#endif
