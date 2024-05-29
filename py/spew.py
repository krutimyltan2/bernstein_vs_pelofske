# Essentially copied from
#   https://github.com/epelofske65537/binary_tree_Batch_GCD
#

import random
from utilities import generate_weak_keys, read_primes_from_stdin

primes = read_primes_from_stdin()
bitlength = primes[0].bit_length()

for N in range(10000+5000, 120000+5000, 5000):
  for WEAK in [2, 100, 1000]:
    print(WEAK, N)
    tracking, unique_shared_primes = generate_weak_keys(primes, N, WEAK, bitlength)
    moduli_init = list(tracking.keys())
    random.shuffle(moduli_init)
    moduli = list(moduli_init.copy())
    file = open("generated/spew_WEAK"+"{:04}".format(WEAK)+"_"+"{:06}".format(N)+"_"+"{:04}".format(bitlength)+".txt", "w")
    for modulus in moduli:
        file.write(hex(modulus)[2:] + "\n")
    file.close()
