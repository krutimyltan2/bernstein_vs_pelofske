#include <err.h>
#include <fmpz.h>
#include <fmpz_vec.h>
#include <stdio.h>
#include <stdlib.h>

#include "prodtree.h"

static inline slong
upper_bound_2pow(const slong x)
{
  slong r = 1;

  while (r < x) {
    r <<= 1;

    if (r == 0) {
      err(EXIT_FAILURE, "upper bound 2pow failure");
    }
  }

  return r;
}

slong
prodtree_compute(fmpz **res, const fmpz *v, slong nv)
{
  slong ubound = upper_bound_2pow(nv);
  slong tree_size = 2 * ubound - 1;
  slong i, j;

  *res = _fmpz_vec_init(tree_size);

  // row 0, v and padded with ones
  for (i = 0; i < nv; i++) {
    fmpz_set(&(*res)[i], &v[i]);
  }
  for (i = nv; i < ubound; i++) {
    fmpz_set_ui(&(*res)[i], 1);
  }

  // rest
  j = 0;
  for (i = ubound; i < tree_size; i++) {
    fmpz_mul(&(*res)[i], &(*res)[j], &(*res)[j + 1]);
    j += 2;
  }

  return tree_size;
}

void
prodtree_pprint(const fmpz *v, const slong nv)
{
  slong i, j = 0, row_len = (nv + 1) >> 1;

  for (i = 0; i < nv; i++) {
    fmpz_print(&v[i]);
    printf(" ");

    j++;

    if (j == row_len) {
      printf("\n");
      row_len >>= 1;
      j = 0;
    }
  }
}
