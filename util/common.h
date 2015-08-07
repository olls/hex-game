#include <stdint.h>

#define bool32 uint32_t
#define true   1
#define false  0


void
error(char * mgs, ...);

uint64_t
get_us();

void
assert(bool32 cond);

void *
allocate(void * game_memory, void ** mem_pos, size_t size, size_t total);
