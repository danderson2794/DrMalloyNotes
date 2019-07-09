#include <iostream>
#include <fstream>
#include "triangle.h"

int main (int , char*[]) {
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    std::cout << "Failed to initialize SDL2" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Window* window = SDL_CreateWindow(
      "Drawing a Triangle", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH, HEIGHT, SDL_WINDOW_SHOWN
  );

  SDL_Renderer* renderer = SDL_CreateRenderer( 
    window, -1, SDL_RENDERER_ACCELERATED
  );

  // Background will be rendered in this color:
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

  // Clear window
  SDL_RenderClear( renderer );

  Triangle triangle(renderer);

  std::ifstream infile( "data/triangles.dat", std::ios::in );
  if ( !infile ) {
    std::cerr << "data/triangles.dat could not be opened\n";
    return 1;
  }

  int number;
  int coords[6];
  int index = 0;
  while ( infile >> number ) {
    coords[index++] = number;
  }

  Vector2f v0(coords[0], coords[1]);
  Vector2f v1(coords[2], coords[3]);
  Vector2f v2(coords[4], coords[5]);
  SDL_Color blue = {0, 0, 255, 255};
  triangle.drawTriangle( blue, v0, v1, v2 );
  SDL_Color red = {255, 0, 0, 255};
  v2[0] = 200; 
  triangle.drawTriangle( red, v0, v1, v2 );

  // The next line does the render:
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
