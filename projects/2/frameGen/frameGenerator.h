#include <string>
#include <SDL.h>

class FrameGenerator {
public:
  FrameGenerator(SDL_Renderer*, SDL_Window*, int, int, const std::string&);
  void makeFrame();
  FrameGenerator(const FrameGenerator&) = delete ;
  FrameGenerator& operator=(const FrameGenerator&) = delete ;
private:
  SDL_Renderer* const renderer;
  SDL_Window* const window;
  const int WIDTH;
  const int HEIGHT;
  const std::string USERNAME;
};
