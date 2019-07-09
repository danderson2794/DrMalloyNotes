#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for ( auto it : sprites ) {
    delete it;
  }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  explosionsFinished(false)
{
  Drawable* s = new Sprite("yellowstar");
  s->setScale(2);
  sprites.push_back(s);
  sprites.emplace_back(new MultiSprite("coin")),

  s = new Sprite("yellowstar");
  sprites.push_back(s);

  sprites.push_back( new MultiSprite("SpinningStar") );

  Viewport::getInstance().setObjectToTrack(sprites.back());
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  std::stringstream strm;
  strm << "fps: " << clock.getFps();
  io.writeText(strm.str(), 30, 60);
  if ( sprites.size() == 0 && explosionsFinished ) {
    io.writeText("Press R to Restart the game", 250, 200);
    clock.pause();
  }
  strm.clear();
  strm.str("");
  strm << sprites.size() << " sprites remaining";
  io.writeText(strm.str(), 30, 90);
  io.writeText("Press E to explode a sprite", 450, 30);
  io.writeText("Restart when all sprites are exploded", 450, 60);

  for(auto* s : sprites) s->draw();
  if ( sprites.size() > 0 ) viewport.draw();
  SDL_RenderPresent(renderer);
}


void Engine::update(Uint32 ticks) {
  std::vector<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    if ( (*ptr)->explosionDone() ) {
      delete (*ptr);
      ptr = sprites.erase(ptr);
      if ( sprites.size() > 0 ) {
        Viewport::getInstance().setObjectToTrack(sprites.back());
      }
      else {
        explosionsFinished = true;
      }
    }
    else ++ptr;
  }
  
  world.update();
  viewport.update(); // always update viewport last
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          // Disabled for this demo
        }
        if ( keystate[SDL_SCANCODE_E] && sprites.size() > 0) {
          sprites.back()->explode();
        }
      }
    }

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
    }
  }
  return false;
}
