#ifndef _PRODTREE_H_
#define _PRODTREE_H_

/**
 * Compute a prodtree from a vector.
 *
 * Given a vector v of length bv we first pad a product tree is
 * constructed by first padding the vector with ones to make it a vector
 * of length a power of 2. This vector forms the leaves of the product
 * tree, and the remaining (complete binary) tree is formed by takning
 * the pairwise product of the children of a node.
 *
 * This function allocates a new vector for the tree, the function
 * calling this has to free the tree.
 *
 * @param res  pointer to the vector to initialize
 * @param v    vector to compute the product tree from
 * @param nv   size of the vector n
 * @returns size of the product tree
 */
slong prodtree_compute(fmpz **res, const fmpz *v, slong nv);

/**
 * Pretty print a product tree.
 *
 * @param v   the product tree to print (as a vector)
 * @param nv  the size (number of nodes) of the prouct tree
 */
void prodtree_pprint(const fmpz *v, const slong nv);

#endif
