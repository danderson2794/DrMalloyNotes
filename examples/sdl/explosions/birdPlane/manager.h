#include <SDL.h>
#include <vector>
#include <list>
#include <string>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "multisprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const Gamedata* gdata;
  const IOManager& io;
  Clock& clock;
  SDL_Surface* screen;

  SDL_Surface* planeSurface;
  SDL_Surface* crowSurface;
  SDL_Surface* dyingcrowSurface;
  std::vector<Frame*> planeFrames;
  std::vector<Frame*> crowFrames;
  std::vector<Frame*> dyingcrowFrames;

  std::list<Drawable*> sprites;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void drawBackground() const;
  void makePlane();
  void explodeSprite(const std::string&);
  void makeCrow();
  void makeDyingcrow();
  void killCrow();
  void draw() const;
  void update();
};
