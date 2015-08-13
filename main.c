#include <time.h>
#include <SDL2/SDL.h>

#include "util/common.h"

#define MEM (1024 * 1024) // 1MB

#define WINDOW_WIDTH  360
#define WINDOW_HEIGHT 480
#define FPS 30

void
hex(v2 hex_pos, uint32_t radius, uint32_t * pixels)
{
  v2 component;
  component.x = radius;
  component.y = radius * sqrt(3) * .5f;

  for (int32_t offset_y = -component.y;
       offset_y < component.y;
       offset_y++)
  {
    for (int32_t offset_x = -component.x;
         offset_x < component.x;
         offset_x++)
    {
      v2 pos = {hex_pos.x + offset_x, hex_pos.y + offset_y};

      if (absInt32(offset_x) < radius * (component.y - absInt32(offset_y) * .5f) / component.y)
      {
        pixels[pos.y * WINDOW_WIDTH + pos.x] = 0;
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

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window * window = SDL_CreateWindow("A Hex Game",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

  // The pixel buffer
  uint32_t * pixels = (uint32_t *)game_memory_pos;
  game_memory_pos += WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t);
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
           pixelPointer.y < WINDOW_HEIGHT;
           pixelPointer.y++)
      {
        for (pixelPointer.x = 0;
             pixelPointer.x < WINDOW_WIDTH;
             pixelPointer.x++)
        {
          pixels[pixelPointer.y * WINDOW_WIDTH + pixelPointer.x] = 0x00FFFFFF;
        }
      }

      // Draw

      v2 hex_pos = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
      uint32_t radius = minInt32(WINDOW_WIDTH, WINDOW_HEIGHT)/3;
      hex(hex_pos, radius, pixels);

      // Flip pixels
      for (uint32_t y = 0;
           y < WINDOW_HEIGHT / 2;
           y++)
      {
        for (uint32_t x = 0;
             x < WINDOW_WIDTH;
             x++)
        {
          uint32_t top_pixel = pixels[y * WINDOW_WIDTH + x];
          pixels[y * WINDOW_WIDTH + x] = pixels[(WINDOW_HEIGHT - y - 1) * WINDOW_WIDTH + x];
          pixels[(WINDOW_HEIGHT - y - 1) * WINDOW_WIDTH + x] = top_pixel;
        }
      }

      SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(uint32_t));

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
