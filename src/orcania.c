#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "../include/orcania.h"

/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 */

/**
 * char * str_replace(const char * source, char * str_old, char * str_new)
 * replace all occurences of str_old by str_new in the string source
 * return a char * with the str_new value
 * return NULL on error
 * returned value must be free'd after use
 */
char * str_replace(const char * source, const char * str_old, const char * str_new) {
  char * to_return, * ptr, * pre, * next;
  size_t len, pre_len;
  
  if (source == NULL || str_old == NULL || str_new == NULL) {
    return NULL;
  }
  
  ptr = strstr(source, str_old);
  if (ptr == NULL) {
    return o_strdup(source);
  } else {
    pre_len = ptr-source;
    pre = o_malloc((pre_len+1)*sizeof(char));
    if (pre == NULL) {
      return NULL;
    }
    memcpy(pre, source, pre_len);
    pre[pre_len] = '\0';
    
    next = str_replace(source+strlen(pre)+strlen(str_old), str_old, str_new);
    if (next == NULL) {
      o_free(pre);
      return NULL;
    }
    len = ((ptr-source)+strlen(str_new)+strlen(next));
    to_return = o_malloc((len+1)*sizeof(char));
    if (to_return == NULL) {
      o_free(pre);
      o_free(next);
      return NULL;
    }
    if (snprintf(to_return, (len+1), "%s%s%s", pre, str_new, next) < 0) {
      o_free(pre);
      o_free(next);
      o_free(to_return);
      return NULL;
    }
    o_free(pre);
    o_free(next);
    return to_return;
  }
}

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 */
char * msprintf(const char * message, ...) {
  va_list argp, argp_cpy;
  size_t out_len = 0;
  char * out = NULL;
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // We make a copy because in some architectures, vsnprintf can modify argp
    out_len = vsnprintf(NULL, 0, message, argp);
    out = o_malloc(out_len+sizeof(char));
    if (out == NULL) {
      return NULL;
    }
    vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}

/**
 * o_strdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strdup(const char * source) {
  return (source==NULL?NULL:o_strndup(source, strlen(source)));
}

/**
 * o_strndup
 * a modified strndup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strndup(const char * source, size_t len) {
  char *new_str;

  if (source == NULL) {
    return NULL;
  } else {
    new_str = o_malloc(len + 1);
    if(!new_str) {
      return NULL;
    }

    memcpy(new_str, source, len);
    new_str[len] = '\0';
    return new_str;
  }
}

/**
 * o_strcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strcmp(p1, p2);
  }
}

/**
 * o_strncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strncmp(p1, p2, n);
  }
}

/**
 * o_strcpy
 * a modified strcpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strcpy(char * p1, const char * p2) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strcpy(p1, p2);
  }
}

/**
 * o_strncpy
 * a modified strncpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strncpy(char * p1, const char * p2, size_t n) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strncpy(p1, p2, n);
  }
}

/**
 * o_strcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcasecmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strcasecmp(p1, p2);
  }
}

/**
 * o_strncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncasecmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strncasecmp(p1, p2, n);
  }
}

/**
 * o_strstr
 * a modified strstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strstr(const char * haystack, const char * needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strstr(haystack, needle);
  }
}

/**
 * o_strchr
 * a modified strchr function that don't crash when haystack is NULL
 */
char * o_strchr(const char * haystack, int c) {
  if (haystack == NULL) {
    return NULL;
  } else {
    return strchr(haystack, c);
  }
}

/**
 * o_strrchr
 * a modified strrchr function that don't crash when haystack is NULL
 */
char * o_strrchr(const char * haystack, int c) {
  if (haystack == NULL) {
    return NULL;
  } else {
    return strrchr(haystack, c);
  }
}

#if defined(__linux__) || defined(__GLIBC__) || defined(_WIN32)
static char *strnstr(const char *haystack, const char *needle, size_t len) {
  int i;
  size_t needle_len;

  /* segfault here if needle is not NULL terminated */
  if (0 == (needle_len = strlen(needle)))
    return (char *)haystack;

  for (i=0; i<=(int)(len - needle_len); i++) {
    if ((haystack[0] == needle[0]) && (0 == strncmp(haystack, needle, needle_len)))
      return (char *)haystack;

    haystack++;
  }
  return NULL;
}
#endif

#ifdef _WIN32
static char *strcasestr(const char *haystack, const char *needle) {
  size_t n;
  if (haystack == NULL || needle == NULL) {
    return NULL;
  }
  n = o_strlen(needle);
  while (*haystack) {
    if (!strnicmp(haystack++, needle, n)) {
      return (char *)(haystack-sizeof(char));
    }
  }
  return NULL;
}
#endif

/**
 * o_strnstr
 * a modified strnstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strnstr(const char * haystack, const char * needle, size_t len) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strnstr(haystack, needle, len);
  }
}

/**
 * o_strcasestr
 * a modified strcasestr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strcasestr(const char * haystack, const char * needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strcasestr(haystack, needle);
  }
}

/**
 * o_strlen
 * a modified version of strlen that don't crash when s is NULL
 */
size_t o_strlen(const char * s) {
  if (s == NULL) {
    return 0;
  } else {
    return strlen(s);
  }
}

/**
 * Split a string into an array of strings using separator string
 * return the number of elements to be returned, 0 on error
 * if return_array is not NULL, set the returned array in it
 * return_array is an array of char * ending with a NULL value
 * return_array must be free'd after use
 * you can use free_string_array to free return_array
 */
int split_string(const char * string, const char * separator, char *** return_array) {
  int result = 0;
  char * token;
  const char * begin = string;
  
  if (string != NULL && separator != NULL) {
    if (return_array != NULL) {
      *return_array = NULL;
    }
    result = 1;
    token = strstr(begin, separator);
    while (token != NULL) {
      if (return_array != NULL) {
        (*return_array) = o_realloc((*return_array), (result + 1)*sizeof(char*));
        if ((*return_array) != NULL) {
          (*return_array)[result-1] = o_strndup(begin, (token-begin));
          (*return_array)[result] = NULL;
        }
      }
      result++;
      begin = token+strlen(separator);
      token = strstr(begin, separator);
    }
    if (return_array != NULL) {
      (*return_array) = o_realloc((*return_array), (result + 1)*sizeof(char*));
      if ((*return_array) != NULL) {
        (*return_array)[result-1] = o_strdup(begin);
        (*return_array)[result] = NULL;
      }
    }
  }
  return result;
}

/**
 * Clean an array of strings
 */
void free_string_array(char ** array) {
  int i;
  if (array != NULL) {
    for (i=0; array[i] != NULL; i++) {
      o_free(array[i]);
      array[i] = NULL;
    }
    o_free(array);
  }
}

/**
 * Remove string of beginning and ending whitespaces
 */
char * trimwhitespace(char * str) {
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(isspace((unsigned char)*str)) str++;

  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}

/**
 * Check if an array of string has a specified value, case sensitive
 */
int string_array_has_value(const char ** array, const char * needle) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strcmp(array[i], needle) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case insensitive
 */
int string_array_has_value_case(const char ** array, const char * needle) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strcasecmp(array[i], needle) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case sensitive, limit to len characters
 */
int string_array_has_value_n(const char ** array, const char * needle, size_t len) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strncmp(array[i], needle, len) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case insensitive, limit to len characters
 */
int string_array_has_value_ncase(const char ** array, const char * needle, size_t len) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strncasecmp(array[i], needle, len) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified trimmed value
 */
int string_array_has_trimmed_value(const char ** array, const char * needle) {
  int i, to_return = 0;
  char * duplicate_needle, * trimmed_needle, * duplicate_value, * trimmed_value;
  if (array != NULL && needle != NULL) {
    duplicate_needle = o_strdup(needle);
    if (duplicate_needle != NULL) {
      trimmed_needle = trimwhitespace(duplicate_needle);
      for (i=0; array[i] != NULL && !to_return; i++) {
        duplicate_value = o_strdup(array[i]);
        if (duplicate_value == NULL) {
          break;
        } else {
          trimmed_value = trimwhitespace(duplicate_value);
          if (o_strcmp(trimmed_value, trimmed_needle) == 0) {
            to_return = 1;
          }
        }
        o_free(duplicate_value);
      }
    }
    o_free(duplicate_needle);
  }
  return to_return;
}

#ifndef U_DISABLE_JANSSON
/**
 * json_t * json_search(json_t * haystack, json_t * needle)
 * jansson library addon
 * Look for an occurence of needle within haystack
 * If needle is present in haystack, return the reference to the json_t * that is equal to needle
 * If needle is not found, return NULL
 */
json_t * json_search(json_t * haystack, json_t * needle) {
  json_t * value1, * value2;
  size_t index;
  const char * key;

  if (!haystack || !needle)
    return NULL;

  if (haystack == needle)
    return haystack;

  // If both haystack and needle are the same type, test them
  if (json_typeof(haystack) == json_typeof(needle) && !json_is_object(haystack))
    if (json_equal(haystack, needle))
      return haystack;

  // If they are not equals, test json_search in haystack elements recursively if it's an array or an object
  if (json_is_array(haystack)) {
    json_array_foreach(haystack, index, value1) {
      if (json_equal(value1, needle)) {
        return value1;
      } else {
        value2 = json_search(value1, needle);
        if (value2 != NULL) {
          return value2;
        }
      }
    }
  } else if (json_is_object(haystack) && json_is_object(needle)) {
    int same = 1;
    json_object_foreach(needle, key, value1) {
      value2 = json_object_get(haystack, key);
      if (!json_equal(value1, value2)) {
        same = 0;
      }
    }
    if (same) {
      return haystack;
    }
  } else if (json_is_object(haystack)) {
    json_object_foreach(haystack, key, value1) {
      if (json_equal(value1, needle)) {
        return value1;
      } else {
        value2 = json_search(value1, needle);
        if (value2 != NULL) {
          return value2;
        }
      }
    }
  }
  return NULL;
}

/**
 * Check if the result json object has a "result" element that is equal to value
 */
int check_result_value(json_t * result, const int value) {
  return (result != NULL && 
          json_is_object(result) && 
          json_object_get(result, "result") != NULL && 
          json_is_integer(json_object_get(result, "result")) && 
          json_integer_value(json_object_get(result, "result")) == value);
}
#endif
