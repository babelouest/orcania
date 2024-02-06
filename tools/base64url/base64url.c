/**
 * 
 * base64url: Base64Url encode or decode FILE, or standard input, to standard output.
 * 
 * Copyright 2021-2022 Nicolas Mora <mail@babelouest.org>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE
 * License as published by the Free Software Foundation;
 * version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU GENERAL PUBLIC LICENSE for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <ctype.h>
#include <orcania.h>

#ifdef _MSC_VER
#include <io.h>
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif

#define _BASE64URL_VERSION "0.9"

#define ACTION_ENCODE 0
#define ACTION_DECODE 1

#define DEFAULT_WRAP 76

#define SIZE 100

static void print_output(const unsigned char * output, size_t output_len, size_t wrap, short int ignore) {
  size_t i;
  for (i=0; i<output_len; i++) {
    if (i && wrap && !(i%wrap)) {
      fputs("\n", stdout);
    }
    if (!ignore || isprint(output[i])) {
      fputc(output[i], stdout);
    }
  }
}

static void print_help(FILE * output, const char * command) {
  fprintf(output, "base64url - Base64Url encode or decode FILE, or standard input, to standard output.\n");
  fprintf(output, "\nUsage: %s [OPTIONS]", command);
  fprintf(output, "\n");
  fprintf(output, "Version %s\n", _BASE64URL_VERSION);
  fprintf(output, "\n");
  fprintf(output, "Copyright 2021-2022 Nicolas Mora <mail@babelouest.org>\n");
  fprintf(output, "\n");
  fprintf(output, "This program is free software; you can redistribute it and/or\n");
  fprintf(output, "modify it under the terms of the GPL 3\n");
  fprintf(output, "\n");
  fprintf(output, "Command-line options:\n");
  fprintf(output, "\n");
  fprintf(output, "-d, --decode\n");
  fprintf(output, "\tDecode data\n");
  fprintf(output, "-i, --ignore-garbage\n");
  fprintf(output, "\twhen decoding, ignore non-alphabet characters\n");
  fprintf(output, "-w, --wrap <COLS>\n");
  fprintf(output, "\twrap encoded lines after COLS character (default 76).  Use 0 to disable line wrapping\n");
  fprintf(output, "-f, --file <FILE_NAME>\n");
  fprintf(output, "\tEncode or decode FILE_NAME content - if this option is missing, red from stdin\n");
  fprintf(output, "-h, --help\n");
  fprintf(output, "\tdisplay this help and exit\n");
  fprintf(output, "-v, --version\n");
  fprintf(output, "\toutput version information and exit\n");
}

static unsigned char * get_file_content(const char * file_path, size_t * length) {
  unsigned char * buffer = NULL;
  size_t res;
  FILE * f;

  f = fopen (file_path, "rb");
  if (f) {
    fseek (f, 0, SEEK_END);
    *length = (size_t)ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = o_malloc(((*length)+1)*sizeof(char));
    if (buffer) {
      res = fread (buffer, 1, *length, f);
      if (res != *length) {
        *length = 0;
        fprintf(stderr, "fread warning, reading %zu while expecting %zu", res, *length);
      }
    }
    fclose (f);
  } else {
    fprintf(stderr, "error opening file %s\n", file_path);
  }
  
  return buffer;
}

static unsigned char * get_stdin_content(size_t * length) {
  unsigned char * out = NULL, buffer[SIZE];
  ssize_t read_length;

  *length = 0;
  while ((read_length = read(0, buffer, SIZE)) > 0) {
    out = o_realloc(out, (*length)+(size_t)read_length+1);
    memcpy(out+(*length), buffer, (size_t)read_length);
    (*length) += (size_t)read_length;
    out[(*length)] = '\0';
  }
  if ((*length) && (out[(*length)-1] == '\n' || out[(*length)-1] == '\r')) {
    out[(*length)-1] = '\0';
    (*length)--;
  }
  return out;
}

int main(int argc, char ** argv) {
  short int action = ACTION_ENCODE, ignore = 0;
  unsigned long int wrap = DEFAULT_WRAP;
  size_t s_wrap = DEFAULT_WRAP;
  const char * short_options = "d::i::w:f:v::h";
  int next_option, ret = 0, exit_loop = 0;
  char * file = NULL, * endptr = NULL, * tmp = NULL;
  unsigned char * input = NULL, * output = NULL;
  size_t input_len = 0, output_len = 0;
  static const struct option long_options[]= {
    {"decode", no_argument, NULL, 'd'},
    {"ignore-garbage", no_argument, NULL, 'i'},
    {"wrap", required_argument, NULL, 'w'},
    {"file", required_argument, NULL, 'f'},
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
  };

  do {
    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
    
    switch (next_option) {
      case 'd':
        action = ACTION_DECODE;
        break;
      case 'i':
        ignore = 1;
        break;
      case 'w':
        wrap = strtoul(optarg, &endptr, 10);
        if (*endptr == '\0' && wrap <= SIZE_MAX) {
          s_wrap = (size_t)wrap;
        } else {
          print_help(stderr, argv[0]);
          exit_loop = 1;
          ret = 1;
        }
        break;
      case 'f':
        o_free(file);
        file = o_strdup(optarg);
        break;
      case 'v':
        fprintf(stdout, "%s %s\n", argv[0], _BASE64URL_VERSION);
        fprintf(stdout, "Copyright 2021-2022 Nicolas Mora <mail@babelouest.org>\n");
        fprintf(stdout, "This program is free software; you can redistribute it and/or\n");
        fprintf(stdout, "modify it under the terms of the GPL 3\n");
        exit_loop = 1;
        break;
      case 'h':
        print_help(stdout, argv[0]);
        exit_loop = 1;
        break;
      default:
        break;
    }
  } while (next_option != -1 && !exit_loop);
  
  if (!exit_loop) {
    if (file != NULL) {
      input = get_file_content(file, &input_len);
    } else {
      input = get_stdin_content(&input_len);
    }
    
    if (input != NULL && input_len) {
      if (action == ACTION_ENCODE) {
        if (o_base64url_encode(input, input_len, NULL, &output_len)) {
          if (output_len) {
            if ((output = o_malloc(output_len+4)) != NULL) {
              if (o_base64url_encode(input, input_len, output, &output_len)) {
                print_output(output, output_len, s_wrap, ignore);
              } else {
                fprintf(stderr, "%s: Error encoding\n", argv[0]);
              }
            } else {
              fprintf(stderr, "%s: Error encoding\n", argv[0]);
            }
          } else {
            fprintf(stderr, "%s: Error encoding\n", argv[0]);
          }
        } else {
          fprintf(stderr, "%s: Error encoding\n", argv[0]);
        }
      } else {
        tmp = str_replace((const char *)input, " ", "");
        o_free(input);
        input = (unsigned char *)tmp;
        tmp = str_replace((const char *)input, "\n", "");
        o_free(input);
        input = (unsigned char *)tmp;
        tmp = str_replace((const char *)input, "\t", "");
        o_free(input);
        input = (unsigned char *)tmp;
        tmp = str_replace((const char *)input, "\v", "");
        o_free(input);
        input = (unsigned char *)tmp;
        tmp = str_replace((const char *)input, "\f", "");
        o_free(input);
        input = (unsigned char *)tmp;
        tmp = str_replace((const char *)input, "\r", "");
        o_free(input);
        input = (unsigned char *)tmp;
        input_len = o_strlen((const char *)input);
        if (o_base64url_decode(input, input_len, NULL, &output_len)) {
          if (output_len) {
            if ((output = o_malloc(output_len+4)) != NULL) {
              if (o_base64url_decode(input, input_len, output, &output_len)) {
                print_output(output, output_len, 0, ignore);
              } else {
                fprintf(stderr, "%s: invalid input\n", argv[0]);
                ret = 1;
              }
            } else {
              fprintf(stderr, "%s: Error decoding\n", argv[0]);
              ret = 1;
            }
          } else {
            fprintf(stderr, "%s: invalid input\n", argv[0]);
            ret = 1;
          }
        } else {
          fprintf(stderr, "%s: invalid input\n", argv[0]);
          ret = 1;
        }
      }
    } else {
      fprintf(stderr, "-- Error no input --\n");
      print_help(stderr, argv[0]);
      ret = 1;
    }
    o_free(input);
    o_free(output);
  }
  o_free(file);
  return ret;
}
