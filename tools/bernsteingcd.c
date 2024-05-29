#include <flint.h>
#include <fmpz_vec.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "batchgcd.h"
#include "fmpzio.h"

int
main(int argc, char *argv[])
{
  fmpz *v, *res;
  slong nv;

  clock_t begin, end;
  double time_spent;

  nv = read_hex_lines(&v);
  res = _fmpz_vec_init(nv);

  begin = clock();

  batch_gcd(res, v, nv);

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%lf\n", time_spent);

//  for (i = 0; i < nv; i++) {
//    fmpz_print(&res[i]);
//    printf("\n");
//  }

  free(v);
  free(res);

  return 0;
}
