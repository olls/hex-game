#include <time.h>
#include <SDL2/SDL.h>

#include "util/common.h"
#include "util/vectors.h"

#define MEM (1024 * 1024) // 1MB

#define FPS 30


typedef struct Game_t
{
  vf2 hex_components;
  uint32_t hex_radius;
  v2 hex_dimensions;
  v2 hex_grid_dimensions;
  v2 window_dimensions;
} Game;


void
hex(v2 hex_pos, uint32_t * pixels, Game game_setup)
{
  vf2 component = mulFloatScalar(game_setup.hex_components, game_setup.hex_radius);
  v2 startOffset = mulScalar(floorVec(component), -1);
  v2 endOffset = floorVec(component);

  if (hex_pos.x + startOffset.x < 0)
  {
    startOffset.x = -hex_pos.x;
  }
  else if (hex_pos.x + startOffset.x > game_setup.window_dimensions.x)
  {
    startOffset.x = game_setup.window_dimensions.x - hex_pos.x;
  }

  if (hex_pos.y + startOffset.y < 0)
  {
    startOffset.y = -hex_pos.y;
  }
  else if (hex_pos.y + startOffset.y > game_setup.window_dimensions.y)
  {
    startOffset.y = game_setup.window_dimensions.y - hex_pos.y;
  }

  v2 offset;
  for (offset.y = startOffset.y;
       offset.y < endOffset.y;
       offset.y++)
  {
    for (offset.x = startOffset.x;
         offset.x < endOffset.x;
         offset.x++)
    {
      v2 pos = addVec(hex_pos, offset);

      if (absInt32(offset.x) < game_setup.hex_radius * (component.y - absInt32(offset.y) * .5f) / component.y)
      {
        pixels[v2ToV1(pos, game_setup.window_dimensions.x)] = 0;
      }
    }
  }
}


int main(int32_t argc, char * argv)
{
  srand(time(NULL));

  void * game_memory = malloc(MEM);
  void * game_memory_pos = game_memory;
  assert(game_memory != NULL);


  Game game_setup;
  game_setup.hex_components = (vf2){1, sqrt(3) * .5f};
  game_setup.hex_radius = 20;
  game_setup.hex_grid_dimensions = (v2){24, 18};

  game_setup.hex_dimensions = floorVec(mulFloatScalar(game_setup.hex_components, game_setup.hex_radius));

  game_setup.window_dimensions = floorVec(mulV2ByVf2(
    game_setup.hex_grid_dimensions,
    mulFloatScalar(game_setup.hex_components, game_setup.hex_radius)));


  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window * window = SDL_CreateWindow("A Hex Game",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game_setup.window_dimensions.x, game_setup.window_dimensions.y, 0);

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, game_setup.window_dimensions.x, game_setup.window_dimensions.y);

  // The pixel buffer
  uint32_t * pixels = (uint32_t *)game_memory_pos;
  game_memory_pos += game_setup.window_dimensions.x * game_setup.window_dimensions.y * sizeof(uint32_t);
  assert(game_memory_pos < game_memory + MEM);

  printf("Starting\n");

  // For average FPS measurement
  uint64_t last_measure = get_us();
  uint32_t frame_count = 0;

  // For FPS timing
  uint64_t last_frame = get_us();
  uint32_t delta_frame;

  bool32 quit = false;
  SDL_Event event;

  while (!quit)
  {
    uint64_t now = get_us();

    // Measure FPS
    if (now >= (last_measure + 1000000))
    {
      // If last measurement was more than 1 sec ago
      last_measure = now;
      printf("%f us/frame\n", 1000000.0f / (double)frame_count);
      frame_count = 0;
    }

    // Render
    if (now >= last_frame + (1000000/FPS))
    {
      delta_frame = now - last_frame;
      last_frame = now;
      frame_count++;

      // Clear screen to white

      v2 pixelPointer;
      for (pixelPointer.y = 0;
           pixelPointer.y < game_setup.window_dimensions.y;
           pixelPointer.y++)
      {
        for (pixelPointer.x = 0;
             pixelPointer.x < game_setup.window_dimensions.x;
             pixelPointer.x++)
        {
          pixels[v2ToV1(pixelPointer, game_setup.window_dimensions.x)] = 0x00FFFFFF;
        }
      }

      // Draw Hexagons

      v2 hex_grid_pos;
      for (hex_grid_pos.x = 0;
           hex_grid_pos.x < game_setup.hex_grid_dimensions.x;
           hex_grid_pos.x += 2)
      {
        for (hex_grid_pos.y = 0;
             hex_grid_pos.y < game_setup.hex_grid_dimensions.y;
             hex_grid_pos.y += 2)
        {
          v2 hex_pixel_pos = mulV2ByV2(game_setup.hex_dimensions, hex_grid_pos);
          hex(hex_pixel_pos, pixels, game_setup);
        }
      }

      //
      // Render
      //

      // Flip pixels
      v2 pos;
      for (pos.y = 0;
           pos.y < game_setup.window_dimensions.y / 2;
           pos.y++)
      {
        for (pos.x = 0;
             pos.x < game_setup.window_dimensions.x;
             pos.x++)
        {
          uint32_t top_pixel = pixels[pos.y * game_setup.window_dimensions.x + pos.x];
          pixels[v2ToV1(pos, game_setup.window_dimensions.x)] = pixels[(game_setup.window_dimensions.y - pos.y - 1) * game_setup.window_dimensions.x + pos.x];
          pixels[(game_setup.window_dimensions.y - pos.y - 1) * game_setup.window_dimensions.x + pos.x] = top_pixel;
        }
      }

      SDL_UpdateTexture(texture, NULL, pixels, game_setup.window_dimensions.x * sizeof(uint32_t));

      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);

    }

    // Get inputs
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
      quit = true;
    }
    else if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == 'w' && event.key.keysym.mod == KMOD_LCTRL)
      {
        quit = true;
      }
    }
  }

  error("Quitting");

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  free(game_memory);

  printf("Finished\n");

  return 0;
}
