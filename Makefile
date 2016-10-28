CC=riscv64-unknown-elf-gcc
CFLAGS=-Wall -O2 -funroll-loops
LDFLAGS=-static

PROGRAMS=bench-soft bench-dma

all: $(PROGRAMS)

bench-soft: bench.o memcpy-soft.o
	$(CC) $^ $(LDFLAGS) -o $@

bench-dma: bench.o memcpy-dma.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o

.PHONY: clean
