#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "vectors.h"


v2
addIntToV2(v2 vec, int32_t addition)
{
  v2 result = vec;

  result.x += addition;
  result.y += addition;

  return result;
}


v2
mulV2ByScalar(v2 vec, int32_t scalar)
{
  v2 result = vec;

  result.x *= scalar;
  result.y *= scalar;

  return result;
}


vf2
mulV2ByFloatScalar(v2 vec, float scalar)
{
  vf2 result;

  result.x = scalar * vec.x;
  result.y = scalar * vec.y;

  return result;
}


v2
addV2(v2 va, v2 vb)
{
  v2 result = {va.x + vb.x, va.y + vb.y};

  return result;
}


v2
subV2(v2 va, v2 vb)
{
  v2 result = {va.x - vb.x, va.y - vb.y};

  return result;
}


v2
mulV2ByV2(v2 va, v2 vb)
{
  v2 result = {va.x * vb.x, va.y * vb.y};

  return result;
}


v2
floorVf2(vf2 f_vec)
{
  v2 result;

  result.x = floorToInt32(f_vec.x);
  result.y = floorToInt32(f_vec.y);

  return result;
}


vf2
addIntToVf2(vf2 vec, int32_t addition)
{
  vf2 result = vec;

  result.x += addition;
  result.y += addition;

  return result;
}


vf2
mulVf2ByScalar(vf2 vec, int32_t scalar)
{
  vf2 result = vec;

  result.x *= scalar;
  result.y *= scalar;

  return result;
}


vf2
mulVf2ByFloatScalar(vf2 vec, float scalar)
{
  vf2 result = vec;

  result.x *= scalar;
  result.y *= scalar;

  return result;
}


vf2
addVf2(vf2 va, vf2 vb)
{
  vf2 result = {va.x + vb.x, va.y + vb.y};

  return result;
}


vf2
subVf2(vf2 va, vf2 vb)
{
  vf2 result = {va.x - vb.x, va.y - vb.y};

  return result;
}


vf2
mulV2ByVf2(v2 va, vf2 vb)
{
  vf2 result = {va.x * vb.x, va.y * vb.y};

  return result;
}


vf2
mulVf2ByV2(vf2 va, v2 vb)
{
  vf2 result = {va.x * vb.x, va.y * vb.y};

  return result;
}


vf2
mulVf2ByVf2(vf2 itva, vf2 vb)
{
  vf2 result = {va.x * vb.x, va.y * vb.y};

  return result;
}


int32_t
v2ToV1(v2 vec, uint32_t stride)
{
  return vec.y * stride + vec.x;
}


void
printV2(v2 * vec)
{
  printf("(%d, %d)\n", vec->x, vec->y);
}


vf2
hexToCart(vHex hex, uint32_t radius)
{
  vf2 result;

  result.x = hex.q;
  result.y = !(hex.q&1) + (2 * (hex.r + (hex.q + (hex.q&1)) / 2));

  return result;
}


vHex
addHexes(vHex ha, vHex hb)
{
  vHex result = {ha.q + hb.q, ha.r + hb.r};

  return result;
}


vHex
mulHexes(vHex ha, vHex hb)
{
  vHex result = {ha.q * hb.q, ha.r * hb.r};

  return result;
}
