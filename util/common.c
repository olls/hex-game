#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdarg.h>

#include "common.h"


void
error(char * msg, ...)
{
  char buf[256];

  va_list aptr;
  va_start(aptr, msg);
  vsnprintf(buf, 256, msg, aptr);
  va_end(aptr);

  fprintf(stderr, "\e[01;31m%s\e[0m\n", buf);
}


uint64_t
get_us()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((uint64_t)tv.tv_sec * (uint64_t)1000000) + (uint64_t)tv.tv_usec;
}


void
assert(bool32 cond)
{
  if (!cond)
  {
    error("Assertion FAILED!! :(");
    exit(1);
  }
}


int32_t
minInt32(int32_t a, int32_t b)
{
  return a <= b ? a : b;
}


uint32_t
absInt32(int32_t x)
{
  return (uint32_t)(x < 0 ? -x : x);
}


int32_t
floorToInt32(float x)
{
  return (int32_t)x;
}


int32_t
squareInt32(int32_t x)
{
  return x * x;
}
