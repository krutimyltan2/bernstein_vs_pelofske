#include <flint.h>
#include <fmpz_vec.h>
#include <stdio.h>
#include <stdlib.h>

#include "fmpzio.h"

static void
print_hex(fmpz_t n)
{
  char *s = fmpz_get_str(NULL, 16, n);
  printf("%s\n", s);
  free(s);
}

static inline void
print_usage(const char *prog) {
  printf("Usage: %s <number of moduli> <bit size of modulus>\n", prog);
}

int
main(int argc, char *argv[])
{
  size_t i;
  uint64_t nmoduli, moduli_size;
  flint_rand_t state;
  fmpz_t p;

  if(argc != 3) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  nmoduli = strtoull(argv[1], NULL, 10);
  moduli_size = strtoull(argv[2], NULL, 10);

  flint_randinit(state);
  fmpz_init(p);

  // fmpz_randprime is not uniform, but good enough for the
  // current purpose

  for (i = 0; i < nmoduli; i++) {
    fmpz_randprime(p, state, moduli_size >> 1, 0);
    while (fmpz_sizeinbase(p, 2) < (moduli_size >> 1)) {
      fmpz_randprime(p, state, moduli_size >> 1, 0);
    }
    print_hex(p);
  }

  flint_randclear(state);
  fmpz_clear(p);

  return 0;
}
