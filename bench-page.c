#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SHIFT 12
#define PAGE_SIZE 4096

static inline void pagein(unsigned long vpn, int npages)
{
	void *ptr = (void *)(vpn << PAGE_SHIFT);
	if (mlock(ptr, npages * PAGE_SIZE)) {
		perror("mlock()");
		abort();
	}
	if (munlock(ptr, npages * PAGE_SIZE)) {
		perror("munlock()");
		abort();
	}
}

unsigned long rdcycle(void)
{
	unsigned long cycle;

	asm volatile ("rdcycle %0" : "=r" (cycle));

	return cycle;
}

int main(int argc, char *argv[])
{
	void *ptr;
	size_t size, npages;
	uintptr_t firstvpn, lastvpn;
	unsigned long start, end;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s size\n", argv[0]);
		abort();
	}
	size = atol(argv[1]);

	ptr = malloc(size);

	firstvpn = ((uintptr_t) ptr) >> PAGE_SHIFT;
	lastvpn = ((uintptr_t) (ptr + size - 1)) >> PAGE_SHIFT;
	npages = lastvpn - firstvpn + 1;

	start = rdcycle();
	pagein(firstvpn, npages);
	end = rdcycle();

	printf("%ld cycles\n", end - start);

	return 0;
}
