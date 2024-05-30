#include <assert.h>
#include <err.h>
#include <fmpz.h>
#include <fmpz_vec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmpzio.h"

#define BASE_ALLOC 1024

static char *
read_all_stdin(const size_t base_alloc)
{
  size_t rsize, cread = 0, current_size = base_alloc;
  char *buffer = malloc(base_alloc * sizeof(*buffer));

  if (buffer == NULL)
    return NULL;

  rsize = fread(buffer, sizeof(*buffer), base_alloc, stdin);

  while (rsize + cread == current_size) {
    cread = current_size;
    current_size <<= 1;
    buffer = realloc(buffer, current_size * sizeof(*buffer));

    if (buffer == NULL)
      return NULL;

    rsize = fread(&buffer[cread], sizeof(*buffer), cread, stdin);
  }

  buffer[rsize + cread] = '\0';

  return buffer;
}

static inline char*
whitespace_sep(char **s) {
  char *orig = *s;

  if(**s == '\0') {
    return NULL;
  }

  while(**s != '\0') {
    if (**s == ' ' || **s == '\t' || **s == '\n') {
      **s = '\0';
      (*s)++;
      break;
    }
    (*s)++;
  }

  return orig;
}

slong
read_hex_lines(fmpz **v)
{
  assert(v != NULL);

  slong i;
  char *r = read_all_stdin(BASE_ALLOC);

  if (r == NULL) {
    err(EXIT_FAILURE, "reading entire stdin failed");
  }

  char *s = r;
  slong ntokens = 0, tokens_alloc = BASE_ALLOC;
  char **tokens = malloc(tokens_alloc * sizeof(*tokens));

  while ((tokens[ntokens] = whitespace_sep(&s)) != NULL) {
    ntokens++;

    if (ntokens == tokens_alloc) {
      tokens_alloc <<= 1;
      tokens = realloc(tokens, tokens_alloc * sizeof(*tokens));

      if (tokens == NULL) {
        err(EXIT_FAILURE, "reallocating tokens failed");
      }
    }
  }

  *v = _fmpz_vec_init(ntokens);

  if (*v == NULL) {
    err(EXIT_FAILURE, "creating vector in read_hex_lines failed");
  }

  for (i = 0; i < ntokens; i++) {
    if (fmpz_set_str(&(*v)[i], tokens[i], 16) != 0) {
      errx(EXIT_FAILURE, "could not interpret \"%s\" as hex integer",
           tokens[i]);
    }
  }

  free(r);
  free(tokens);

  return ntokens;
}
