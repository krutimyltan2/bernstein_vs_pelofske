#include <err.h>
#include <fmpz.h>
#include <fmpz_vec.h>
#include <stdio.h>
#include <stdlib.h>

#include "prodtree.h"
#include "batchgcd.h"

static inline void
remtree_compute(fmpz *tree, const slong tree_size)
{
  slong i = tree_size - 2;
  slong parent_distance = 1;

  while (1) {
    fmpz_mul(&tree[i], &tree[i], &tree[i]);
    fmpz_mod(&tree[i], &tree[i + parent_distance], &tree[i]);
    parent_distance++;
    i--;

    fmpz_mul(&tree[i], &tree[i], &tree[i]);
    fmpz_mod(&tree[i], &tree[i + parent_distance], &tree[i]);
    if(i == 0) break;
    i--;
  }
}

void
batch_gcd(fmpz *r, const fmpz *v, slong n)
{
  fmpz *tree;
  slong tree_size, i;
  
  tree_size = prodtree_compute(&tree, v, n);
  remtree_compute(tree, tree_size);

  for(i = 0; i < n; i++) {
    fmpz_fdiv_q(&r[i], &tree[i], &v[i]);
    fmpz_gcd(&r[i], &r[i], &v[i]);
  }

  free(tree);
}

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


static inline slong
incomplete_prodtree_compute(fmpz** res, const fmpz *v, slong nv)
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

  // rest, not root
  j = 0;
  for (i = ubound; i < tree_size-1; i++) {
    fmpz_mul(&(*res)[i], &(*res)[j], &(*res)[j + 1]);
    j += 2;
  }

  return tree_size;
}

// see: https://github.com/epelofske65537/binary_tree_Batch_GCD
void
pelofske_gcd(fmpz *r, const fmpz *v, slong n)
{
  fmpz *tree;
  fmpz *bvec;
  fmpz *bbtree;
  slong tree_size, i, ninb, bbtree_size;

  tree_size = incomplete_prodtree_compute(&tree, v, n);

  bvec = _fmpz_vec_init(tree_size);
  ninb = 0;

  for(i = 0; i < tree_size-1; i+=2) {
    fmpz_gcd(&bvec[ninb], &tree[i], &tree[i+1]);
    if (fmpz_cmp_ui(&bvec[ninb], 1) != 0) {
      ninb++;
    } 
  }

  bbtree_size = prodtree_compute(&bbtree, bvec, ninb); 

  for(i = 0; i < n; i++) {
    fmpz_gcd(&r[i], &bbtree[bbtree_size-1], &v[i]);
  }

  _fmpz_vec_clear(tree, tree_size);
  _fmpz_vec_clear(bvec, tree_size);
  _fmpz_vec_clear(bbtree, bbtree_size);
}
