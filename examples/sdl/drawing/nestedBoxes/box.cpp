#include "box.h"

void Box::draw(int x, int y, int w, int h, bool fill) {
  SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
  SDL_Rect r = {x, y, w, h};
  if ( fill ) {
    SDL_RenderFillRect( renderer, &r);
  }
  else {
    SDL_RenderDrawRect( renderer, &r);
  }
}

