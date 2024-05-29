.SUFFIXES: .c .o .so
CC=clang
CFLAGS+=-std=c11 -pedantic -Wall -Werror -Wstrict-prototypes
CFLAGS+=-Wmissing-prototypes -Wmissing-declarations -Wshadow
CFLAGS+=-Wpointer-arith -Wcast-qual -Wsign-compare
#CFLAGS+=-O2 -g
CLAGSS+=-O3 -DNDEBUG
CFLAGS+=-fstack-protector-all -Wtype-limits -fno-common
CFLAGS+=-fno-builtin
CFLAGS+=-I/usr/local/include

BUILD=build

OBJ=\
fmpzio.o\
prodtree.o\
batchgcd.o
TOOLS=\
tools/gen\
tools/bernsteingcd\
tools/pelofskegcd

TOOLS_DIR=tools

all: $(OBJ) $(TOOLS)

.c.o:
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

# -- tools

tools/gen: $(OBJ) $(@:S/$/.c/)
	$(CC) -I. $(CFLAGS) -o $@ $(TOOLS_DIR)/gen.c $(OBJ) $(LDFLAGS)

tools/pelofskegcd: $(OBJ) $(@:S/$/.c/)
	$(CC) -I. $(CFLAGS) -o $@ $(TOOLS_DIR)/pelofskegcd.c $(OBJ) $(LDFLAGS)

tools/bernsteingcd: $(OBJ) $(@:S/$/.c/)
	$(CC) -I. $(CFLAGS) -o $@ $(TOOLS_DIR)/bernsteingcd.c $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ) $(SHARED) $(TOOLS)
