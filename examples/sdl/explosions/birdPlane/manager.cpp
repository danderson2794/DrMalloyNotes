#include <cmath>
#include "manager.h"
#include "sprite.h"
#include "explodingSprite.h"
#include "dyingCrow.h"

Manager::~Manager() { 
  SDL_FreeSurface(planeSurface);
  SDL_FreeSurface(crowSurface);
  SDL_FreeSurface(dyingcrowSurface);
  for (unsigned i = 0; i < planeFrames.size(); ++i) {
    delete planeFrames[i];
  }
  for (unsigned i = 0; i < crowFrames.size(); ++i) {
    delete crowFrames[i];
  }
  for (unsigned i = 0; i < dyingcrowFrames.size(); ++i) {
    delete dyingcrowFrames[i];
  }
  std::list<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
  delete Gamedata::getInstance();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  planeSurface( io.loadAndSet(gdata->getXmlStr("planeFile"), true) ),
  crowSurface( io.loadAndSet(gdata->getXmlStr("crowFile"), true) ),
  dyingcrowSurface( io.loadAndSet(gdata->getXmlStr("dyingcrowFile"),true) ),
  planeFrames(),
  crowFrames(),
  dyingcrowFrames(),
  sprites( )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  makePlane();
  makeCrow();
  makeDyingcrow();
  atexit(SDL_Quit);
}

void Manager::makePlane() {
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 1, 1) );
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 123, 1) );
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 245, 1) );
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 367, 1) );
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 489, 1) );
  planeFrames.push_back( new Frame(planeSurface, 121, 72, 17, 74) );
  sprites.push_back( new MultiframeSprite("plane", planeFrames) );
}

void Manager::makeCrow() {
  unsigned numberOfFrames = gdata->getXmlInt("crowFrames");
  Uint16 pwidth = gdata->getXmlInt("crowWidth");
  Uint16 pheight = gdata->getXmlInt("crowHeight");
  Uint16 srcX = gdata->getXmlInt("crowSrcX");
  Uint16 srcY = gdata->getXmlInt("crowSrcY");

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * pwidth + srcX;
    crowFrames.push_back( 
      new Frame(crowSurface, pwidth, pheight, frameX, srcY) );
  }
  sprites.push_back( new MultiframeSprite("crow", crowFrames) );
}

void Manager::makeDyingcrow() {
  unsigned numberOfFrames = gdata->getXmlInt("dyingcrowFrames");
  Uint16 pwidth = gdata->getXmlInt("dyingcrowWidth");
  Uint16 pheight = gdata->getXmlInt("dyingcrowHeight");
  Uint16 srcX = gdata->getXmlInt("dyingcrowSrcX");
  Uint16 srcY = gdata->getXmlInt("dyingcrowSrcY");

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * pwidth + srcX;
    dyingcrowFrames.push_back( 
      new Frame(dyingcrowSurface, pwidth, pheight, frameX, srcY) );
  }
}

void Manager::drawBackground() const {
  SDL_FillRect( screen, NULL, 
                SDL_MapRGB(screen->format, 
                           gdata->getXmlInt("backRed"), 
                           gdata->getXmlInt("backGreen"), 
                           gdata->getXmlInt("backBlue")
                          )
              );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void Manager::draw() const {
  drawBackground();
  io.printMessageAt("p for pause", 10, 10);
  io.printMessageAt("x chunk plane", 10, 30);
  io.printMessageAt("c kill crow", 10, 50);
  io.printMessageAt("a chunk both", 10, 70);
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
}

void Manager::update() {
  Uint32 ticks = clock.getElapsedTicks();
  std::list<Drawable*>::iterator ptr = sprites.begin();
  bool updatePtr;
  while ( ptr != sprites.end() ) {
    updatePtr = true;
    (*ptr)->update(ticks);
    ExplodingSprite* sprite = dynamic_cast<ExplodingSprite*>(*ptr);
    if ( sprite && sprite->chunkCount() == 0) {
      updatePtr = false;
      if ( sprite->getName() == "plane" ) {
        sprites.push_back( new MultiframeSprite("plane", planeFrames) );
      }
      if ( sprite->getName() == "crow" ) {
        sprites.push_back( new MultiframeSprite("crow", crowFrames) );
      }
      ptr = sprites.erase(ptr);
      delete sprite;
    }
    else if ( dynamic_cast<Dyingcrow*>(*ptr) && 
              static_cast<Dyingcrow*>(*ptr)->isDead() ) {
      float pos = (*ptr)->X();
      delete (*ptr);
      MultiframeSprite* sprite = new MultiframeSprite("crow", crowFrames);
      sprite->X(pos);
      sprites.push_back( sprite );
      ptr = sprites.erase(ptr);
      updatePtr = false;
    }
    if ( updatePtr) { 
      ++ptr;
    }
  }
}

void Manager::killCrow() {
  std::list<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    Drawable* sprite = dynamic_cast<MultiframeSprite*>(*ptr);
    if ( sprite && sprite->getName() == "crow") {
      MultiframeSprite* dyingCrow = 
         new Dyingcrow("dyingcrow", dyingcrowFrames);
      sprites.push_back( dyingCrow );
      dyingCrow->setPosition( sprite->getPosition() );
      delete sprite;
      ptr = sprites.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Manager::explodeSprite(const string& name) {
  std::list<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    Drawable* sprite = dynamic_cast<MultiframeSprite*>(*ptr);
    if ( sprite && sprite->getName() == name) {
      const Frame* frame = sprite->getFrame();
      Sprite newSprite(sprite->getPosition(), sprite->getVelocity(), 
                       name, frame);
      delete sprite;
      ptr = sprites.erase(ptr);
      sprites.push_back( new ExplodingSprite(newSprite) );
    }
    else ++ptr;
  }
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {
    draw();
    SDL_Flip(screen);
    update();

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_x      : {
          if (!keyCatch) {
            keyCatch = true;
            explodeSprite("plane");
          }
          break;
        }
        case SDLK_c      : {
          if (!keyCatch) {
            keyCatch = true;
            killCrow();
          }
          break;
        }
        case SDLK_a      : {
          if (!keyCatch) {
            keyCatch = true;
            explodeSprite("plane");
            explodeSprite("crow");
          }
          break;
        }
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        default          : break;
      }
    }
  }
}
