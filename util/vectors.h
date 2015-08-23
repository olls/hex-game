typedef struct v2_t
{
  int32_t x;
  int32_t y;
} v2;

typedef struct vf2_t
{
  float x;
  float y;
} vf2;

typedef struct vHex_t
{
  int32_t q;
  int32_t r;
} vHex;

v2
addIntToV2(v2, int32_t);

v2
mulV2ByScalar(v2, int32_t);

vf2
mulV2ByFloatScalar(v2, float);

v2
addV2(v2, v2);

vf2
subVf2(vf2, vf2);

v2
mulV2ByV2(v2, v2);

v2
floorVf2(vf2);

vf2
addIntToVf2(vf2, int32_t);

vf2
mulVf2ByScalar(vf2, int32_t);

vf2
mulVf2ByFloatScalar(vf2, float);

vf2
addVf2(vf2, vf2);

v2
subV2(v2, v2);

vf2
mulV2ByVf2(v2, vf2);

vf2
mulVf2ByV2(vf2, v2);

vf2
mulVf2ByVf2(vf2, vf2);

int32_t
v2ToV1(v2, uint32_t);

void
printV2(v2 *);

vf2
hexToCart(vHex hex, uint32_t);

vHex
addHexes(vHex, vHex);

vHex
mulHexes(vHex, vHex);
