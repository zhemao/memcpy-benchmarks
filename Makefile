CC=riscv64-unknown-linux-gnu-gcc
CFLAGS=-Wall -O2 -funroll-loops
LDFLAGS=-static

PROGRAMS=bench-soft bench-dma bench-page

all: $(PROGRAMS)

bench-soft: bench.o memcpy-soft.o
	$(CC) $^ $(LDFLAGS) -o $@

bench-dma: bench.o memcpy-dma.o
	$(CC) $^ $(LDFLAGS) -o $@

bench-page: bench-page.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o

.PHONY: clean
