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

typedef struct v2_t
{
  int32_t x;
  int32_t y;
} v2;

v2
addScalar(v2 vec, int32_t scalar);

v2
addVec(v2 va, v2 vb);

int32_t
minInt32(int32_t a, int32_t b);

uint32_t
absInt32(int32_t x);
