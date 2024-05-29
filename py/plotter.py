import matplotlib.pyplot as plt
import numpy as np
import sys

xs = []
bys = []
pys = []

fname = sys.argv[1]
size = sys.argv[2]
nweak = sys.argv[3]

for line in open(fname, "r"):
    if line[-1] == "\n":
        line = line[:-1]
    sline = line.split(" ")
    xs.append(int(sline[0], 10))
    bys.append(float(sline[1]))
    pys.append(float(sline[2]))

xa = np.array(xs)
bya = np.array(bys)
pya = np.array(pys)

plt.plot(xa, bya)
plt.plot(xa, pya)

plt.legend(["hashbreaker", "pelofske"])
plt.title(f"size = {size}, # weak = {nweak}")
plt.xlabel("number of moduli")
plt.ylabel("time [seconds]")

#plt.show()
plt.savefig(f"/tmp/plot_{size}_{nweak}.png")
