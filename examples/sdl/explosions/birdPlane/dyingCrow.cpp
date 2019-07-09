#include <iostream>
#include <cmath>
#include "dyingCrow.h"
#include "gamedata.h"
#include <limits>
using std::cout; using std::endl;

void Dyingcrow::advanceFrame(Uint32 ticks) {
	// Frame animation specialized for a dying crow (rip):
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > crowInterval) {
		if (currentFrame < numberOfFrames-1) {
		  ++currentFrame;
		}
		timeSinceLastFrame = 0;
	}
}

Dyingcrow::
Dyingcrow(const std::string& name, const std::vector<Frame*>& fm) :
  MultiframeSprite(name, fm),
  dead(false),
  timeSinceLastFrame( 0 ),
  crowInterval(Gamedata::getInstance()->getXmlInt("dyingcrowFrameInterval"))
{ }

Dyingcrow::Dyingcrow(const Dyingcrow& s) :
  MultiframeSprite(s),
  dead(s.dead),
  timeSinceLastFrame( 0 ),
  crowInterval(s.crowInterval)
{ }

Dyingcrow& Dyingcrow::operator=(const Dyingcrow& rhs) {
  //MultiframeSprite::operator=(rhs);
  dead = rhs.dead;
  std::cout << "FIX THIS" << std::endl;
  return *this;
}

void Dyingcrow::update(Uint32 ticks) { 
  if ( Y() + frameHeight  < worldHeight ) {
    MultiframeSprite::update(ticks);
    advanceFrame(ticks);
  }
  else {
      dead = true;
  }
}

