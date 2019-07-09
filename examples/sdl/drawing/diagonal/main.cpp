#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const std::string TITLE = "Drawing a Filled Rectangle";

int main (int , char*[]) {
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    std::cout << "Failed to initialize SDL2" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(), 
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
  );

  SDL_Renderer* renderer = SDL_CreateRenderer( 
    window, -1, SDL_RENDERER_ACCELERATED
  );

  // Set render color to pink ( background will be rendered in this color )
  SDL_SetRenderDrawColor( renderer, 255, 192, 203, 255 );

  // Clear window
  SDL_RenderClear( renderer );

  SDL_Rect r;
  r.x = 150;
  r.y = 150;
  r.w = 300;
  r.h = 200;

  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );

  // Render rect
  SDL_RenderFillRect( renderer, &r );

  // To set opacity to half: 255/2
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect( renderer, &r );

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
  SDL_RenderDrawLine( renderer, 150, 150, 450, 350);

  // Render the rect to the screen
  SDL_RenderPresent(renderer);

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
