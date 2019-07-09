#include <SDL2/SDL.h>

class Circle {
public:
  Circle(SDL_Renderer* r) : renderer(r) {}
  void drawCircle(SDL_Point center, int radius, const SDL_Color&) const;
private:
  SDL_Renderer* renderer;
};
