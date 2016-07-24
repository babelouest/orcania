#include <string.h>
#include <jansson.h>
#include "orcania.h"

/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * all Angharad modules
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
    return strdup(source);
  } else {
    pre_len = ptr-source;
    pre = malloc((pre_len+1)*sizeof(char));
    if (pre == NULL) {
      return NULL;
    }
    memcpy(pre, source, pre_len);
    pre[pre_len] = '\0';
    
    next = str_replace(source+strlen(pre)+strlen(str_old), str_old, str_new);
    if (next == NULL) {
      free(pre);
      return NULL;
    }
    len = ((ptr-source)+strlen(str_new)+strlen(next));
    to_return = malloc((len+1)*sizeof(char));
    if (to_return == NULL) {
      free(pre);
      free(next);
      return NULL;
    }
    if (snprintf(to_return, (len+1), "%s%s%s", pre, str_new, next) < 0) {
      free(pre);
      free(next);
      free(to_return);
      return NULL;
    }
    free(pre);
    free(next);
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
  va_start(argp, message);
  va_copy(argp_cpy, argp); // We make a copy because in some architectures, vsnprintf can modify argp
  out_len = vsnprintf(NULL, 0, message, argp);
  out = malloc(out_len+sizeof(char));
  if (out == NULL) {
    return NULL;
  }
  vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
  va_end(argp);
  va_end(argp_cpy);
  return out;
}

/**
 * nstrdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * nstrdup(const char * source) {
  return (source==NULL?NULL:strdup(source));
}

/**
 * nstrcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 */
int nstrcmp(const char * p1, const char * p2) {
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
 * nstrncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 */
int nstrncmp(const char * p1, const char * p2, size_t n) {
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
 * nstrcpy
 * a modified strcpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * nstrcpy(char * p1, const char * p2) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strcpy(p1, p2);
  }
}

/**
 * nstrncpy
 * a modified strncpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * nstrncpy(char * p1, const char * p2, size_t n) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strncpy(p1, p2, n);
  }
}

/**
 * nstrcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int nstrcasecmp(const char * p1, const char * p2) {
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
 * nstrncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int nstrncasecmp(const char * p1, const char * p2, size_t n) {
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
 * nstrstr
 * a modified strstr function that don't crash when p1 is NULL or p2 us NULL
 */
char * nstrstr(const char * haystack, const char * needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strstr(haystack, needle);
  }
}

/**
 * nstrlen
 * a modified version of strlen that don't crash when s is NULL
 */
size_t nstrlen(const char * s) {
  if (s == NULL) {
    return -1;
  } else {
    return strlen(s);
  }
}

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
