#include "dma-ext.h"
#include "memcpy.h"

void test_memcpy(void *dst, void *src, size_t size)
{
	dma_write_cr(SEGMENT_SIZE, size);
	dma_write_cr(NSEGMENTS, 1);
	dma_transfer(dst, src);
	asm volatile ("fence");
}
