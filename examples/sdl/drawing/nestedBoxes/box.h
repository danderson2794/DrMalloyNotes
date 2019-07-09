#include <SDL2/SDL.h>

class Box {
public:
  Box(SDL_Renderer* rend) : renderer(rend), color({0,0,0,0}) {}
  void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }
  void draw(int x, int y, int w, int h, bool fill = false);
private:
  SDL_Renderer* renderer;
  SDL_Color color;
};
