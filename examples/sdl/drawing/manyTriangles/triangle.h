#include <SDL2/SDL.h>
#include "vector2f.h"

const int WIDTH = 640;
const int HEIGHT = 480;

class Triangle {
public:
  Triangle(SDL_Renderer* r) : renderer(r) {}
  void drawTriangle(const SDL_Color&, const Vector2f&, const Vector2f&, 
                    const Vector2f&);

private:
  SDL_Renderer* renderer;
  float triangle(Vector2f x, float fuzz, 
          const Vector2f& v0, const Vector2f& v1, const Vector2f& v2);
  float wedge(Vector2f, Vector2f);
  int smallest(int, int, int);
  int largest(int, int, int);
};
