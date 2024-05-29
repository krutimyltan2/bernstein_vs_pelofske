#ifndef _FMPZIO_H_
#define _FMPZIO_H_

#include <fmpz.h>

/**
 * Read a fmpz vector from stdin.
 *
 * The numbers are read from stdin, separated by whitespaces (spaces,
 * tabs and newlines). Returns the size of the resulting vector.
 * Allocates a new vector which needs to be cleared.
 *
 * @param v pointer to vector to initialize
 * @returns the length of the new vector
 */
slong read_hex_lines(fmpz **v);

#endif
