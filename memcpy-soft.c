#include "memcpy.h"
#include <stdint.h>

void test_memcpy(void *dst, void *src, size_t len)
{
	uintptr_t ptr_mask = (uintptr_t) dst | (uintptr_t) src | len;

	if ((ptr_mask & (sizeof(uintptr_t) - 1)) == 0) {
		uintptr_t *d = dst, *s = src;
		size_t n = len / sizeof(uintptr_t);

		for (int i = 0; i < n; i++)
			d[i] = s[i];
	} else {
		char *d = dst, *s = src;

		while (d < (char *)(dst + len))
			*(d++) = *(s++);
	}

	// this is to ensure timing fairness
	asm volatile ("fence");
}


