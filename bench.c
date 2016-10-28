#include "memcpy.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

unsigned long rdcycle(void)
{
	unsigned long cycle;

	asm volatile ("rdcycle %0" : "=r" (cycle));

	return cycle;
}

static inline void fill(uint64_t *a, size_t n)
{
	for (int i = 0; i < n; i++) {
		a[i] = i * 2;
	}
}

static inline void check(uint64_t *a, uint64_t *b, size_t n)
{
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i])
			fprintf(stderr, "Bad data %ld != %ld\n", a[i], b[i]);
	}
}

int main(int argc, char *argv[])
{
	void *src, *dst;
	size_t size;
	unsigned long start, end;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s size\n", argv[0]);
		abort();
	}
	size = atol(argv[1]);

	src = malloc(size);
	dst = malloc(size);

	if (size % sizeof(uint64_t) != 0) {
		fprintf(stderr, "size must be multiple of 8\n");
		abort();
	}
	fill((uint64_t *) src, size / sizeof(uint64_t));

	printf("starting memcpy of %ld bytes from %p to %p\n", size, src, dst);

	asm volatile ("fence");

	start = rdcycle();

	test_memcpy(dst, src, size);

	end = rdcycle();

	check(dst, src, size / sizeof(uint64_t));

	printf("%ld cycles\n", end - start);

	return 0;
}
