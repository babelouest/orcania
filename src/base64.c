/*
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2017-2022, Nicolas Mora <mail@babelouest.org>
 *
 * This software may be distributed under the terms of the BSD license.
 */

#include <string.h>
#include <math.h>
#include "orcania.h"

static const unsigned char base64_table[65] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char base64_url_table[65] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static size_t table_size = 65;

static int _o_base64_encode_agnostic(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len, const unsigned char * table, int right_pad) {
  unsigned char * pos;
  const unsigned char * end, * in;
  size_t olen;
  int line_len;

  olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
  olen += olen / 72; /* line feeds */
  olen++; /* nul termination */
  if (olen < len || src == NULL || out_len == NULL) {
    return 0;
  }

  end = src + len;
  in = src;
  pos = out;
  line_len = 0;
  *out_len = 0;
  while (end - in >= 3) {
    if (pos != NULL) {
      *pos++ = (unsigned char)(table[in[0] >> 2]);
      *pos++ = (unsigned char)(table[((in[0] & 0x03) << 4) | (in[1] >> 4)]);
      *pos++ = (unsigned char)(table[((in[1] & 0x0f) << 2) | (in[2] >> 6)]);
      *pos++ = (unsigned char)(table[in[2] & 0x3f]);
    }
    (*out_len) += 4;
    in += 3;
    line_len += 4;
    if (line_len >= 72) {
      line_len = 0;
    }
  }

  if (end - in) {
    if (pos != NULL) {
      *pos++ = (unsigned char)(table[in[0] >> 2]);
    }
    (*out_len)++;
    if (end - in == 1) {
      if (pos != NULL) {
        *pos++ = (unsigned char)(table[(in[0] & 0x03) << 4]);
        if (right_pad) {
          *pos++ = '=';
        }
      }
      if (right_pad) {
        (*out_len) += 2;
      } else {
        (*out_len)++;
      }
    } else {
      if (pos != NULL) {
        *pos++ = (unsigned char)(table[((in[0] & 0x03) << 4) | (in[1] >> 4)]);
        *pos++ = (unsigned char)(table[(in[1] & 0x0f) << 2]);
      }
      (*out_len) += 2;
    }
    if (pos != NULL && right_pad) {
      *pos++ = '=';
    }
    if (right_pad) {
      (*out_len)++;
    }
  }

  return 1;
}

static int o_base64_decode_agnostic(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len, const unsigned char * table, int right_pad) {
  unsigned char dtable[256], *pos = out, block[4] = {0}, tmp;
  size_t i, count, unpad = 0;
  int pad = 0;
  
  if (src == NULL || !len || out_len == NULL) {
    return 0;
  }

  if (len % 4 == 2) {
    unpad = 2;
  } else if (len % 4 == 3) {
    unpad = 1;
  }

  memset(dtable, 0x80, 256);
  for (i = 0; i < table_size - 1; i++) {
    dtable[table[i]] = (unsigned char) i;
  }
  dtable['='] = 0;

  count = 0;
  for (i = 0; i < len; i++) {
    if (dtable[src[i]] != 0x80) {
      count++;
    }
  }

  if (right_pad && (count == 0 || count % 4)) {
    return 0;
  }

  count = 0;
  *out_len = 0;
  for (i = 0; i < len; i++) {
    if (!o_strchr((const char *)table, src[i]) && src[i] != '=' && src[i] != '\n' && src[i] != '\t' && src[i] != ' ') {
      // character invalid
      return 0;
    }
    tmp = dtable[src[i]];
    if (tmp == 0x80) {
      continue;
    }

    if (src[i] == '=') {
      pad++;
    }
    block[count] = tmp;
    count++;
    if (i == len-1) {
      count = 4;
      (*out_len) -= unpad;
    }
    if (count == 4) {
      if (pos != NULL) {
        *pos++ = (unsigned char)((block[0] << 2)) | (unsigned char)((block[1] >> 4));
        *pos++ = (unsigned char)((block[1] << 4)) | (unsigned char)((block[2] >> 2));
        *pos++ = (unsigned char)((block[2] << 6)) | (unsigned char)(block[3]);
      }
      (*out_len)+=3;
      count = 0;
      if (pad) {
        if (pad == 1) {
          if (pos != NULL) {
            pos--;
          }
          (*out_len)--;
        } else if (pad == 2) {
          if (pos != NULL) {
            pos -= 2;
          }
          (*out_len) -= 2;
        } else {
          /* Invalid padding */
          return 0;
        }
        break;
      }
      memset(block, 0, 4);
    }
  }

  return 1;
}

int o_base64_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len) {
  return _o_base64_encode_agnostic(src, len, out, out_len, base64_table, 1);
}

int o_base64_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  return o_base64_decode_agnostic(src, len, out, out_len, base64_table, 1);
}

int o_base64url_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len) {
  return _o_base64_encode_agnostic(src, len, out, out_len, base64_url_table, 0);
}

int o_base64url_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  return o_base64_decode_agnostic(src, len, out, out_len, base64_url_table, 0);
}

int o_base64url_2_base64(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t index;
  
  if (src != NULL && len && out != NULL && out_len != NULL) {
    memcpy(out, src, len);
    *out_len = len;
    for (index = 0; index < len; index++) {
      if (out[index] == '-') {
        out[index] = '+';
      } else if (out[index] == '_') {
        out[index] = '/';
      }
    }
    if (len % 4 == 2) {
      out[len] = '=';
      out[len+1] = '=';
      (*out_len) += 2;
    } else if (len % 4 == 3) {
      out[len] = '=';
      (*out_len)++;
    }
    res = 1;
  }
  return res;
}

int o_base64_2_base64url(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t index;
  
  if (src) {
    memcpy(out, src, len);
    *out_len = len;
    for (index = 0; index < len; index++) {
      if (out[index] == '+') {
        out[index] = '-';
      } else if (out[index] == '/') {
        out[index] = '_';
      }
    }
    while (out[(*out_len)-1] == '=') {
      (*out_len)--;
    }
    res = 1;
  }
  
  return res;
}

int o_base64_encode_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;

  if (dat != NULL) {
    dat->size = 0;
    if ((ret = o_base64_encode(src, len, NULL, &dat->size)) && dat->size) {
      if ((dat->data = o_malloc(dat->size+2)) != NULL) {
        memset(dat->data, 0, dat->size+2);
        ret = o_base64_encode(src, len, dat->data, &dat->size);
      } else {
        ret = 0;
      }
    }
  }
  return ret;
}

int o_base64_decode_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;

  if (dat != NULL) {
    dat->size = 0;
    if ((ret = o_base64_decode(src, len, NULL, &dat->size)) && dat->size) {
      if ((dat->data = o_malloc(dat->size+2)) != NULL) {
        memset(dat->data, 0, dat->size+2);
        ret = o_base64_decode(src, len, dat->data, &dat->size);
      } else {
        ret = 0;
      }
    }
  }
  return ret;
}

int o_base64url_encode_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;

  if (dat != NULL) {
    dat->size = 0;
    if ((ret = o_base64url_encode(src, len, NULL, &dat->size)) && dat->size) {
      if ((dat->data = o_malloc(dat->size+2)) != NULL) {
        memset(dat->data, 0, dat->size+2);
        ret = o_base64url_encode(src, len, dat->data, &dat->size);
      } else {
        ret = 0;
      }
    }
  }
  return ret;
}

int o_base64url_decode_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;

  if (dat != NULL) {
    dat->size = 0;
    if ((ret = o_base64url_decode(src, len, NULL, &dat->size)) && dat->size) {
      if ((dat->data = o_malloc(dat->size+2)) != NULL) {
        memset(dat->data, 0, dat->size+2);
        ret = o_base64url_decode(src, len, dat->data, &dat->size);
      } else {
        ret = 0;
      }
    }
  }
  return ret;
}

int o_base64url_2_base64_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;
  unsigned char * out = NULL;

  if (dat != NULL) {
    dat->size = 0;
    if ((out = o_malloc(len+4)) != NULL) {
      if ((ret = o_base64url_2_base64(src, len, out, &dat->size)) && dat->size) {
        if ((dat->data = o_malloc(dat->size)) != NULL) {
          memcpy(dat->data, out, dat->size);
        }
      }
    }
  }
  o_free(out);
  return ret;
}

int o_base64_2_base64url_alloc(const unsigned char * src, size_t len, struct _o_datum * dat) {
  int ret = 0;
  unsigned char * out = NULL;

  if (dat != NULL) {
    dat->size = 0;
    if ((out = o_malloc(len)) != NULL) {
      if ((ret = o_base64_2_base64url(src, len, out, &dat->size)) && dat->size) {
        if ((dat->data = o_malloc(dat->size)) != NULL) {
          memcpy(dat->data, out, dat->size);
        }
      }
    }
  }
  o_free(out);
  return ret;
}
