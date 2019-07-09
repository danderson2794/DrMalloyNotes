#include "multisprite.h"
#include "gameData.h"
#include "imageFactory.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           Gamedata::getInstance().getXmlFloat(name+"/scale")
           ),
  images( ImageFactory::getInstance()->getImages(name) ),
  rotating(false),
  angle(0.0f),
  rotateSpeed( Gamedata::getInstance().getXmlInt(name+"/rotateSpeed") ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void MultiSprite::draw() const { 
  if ( rotating ) {
    images[currentFrame]->drawRotated(getX(), getY(), getScale(), angle);
  }
  else {
    images[currentFrame]->draw(getX(), getY(), getScale());
  }
}

void MultiSprite::rotate() { 
  if ( !rotating ) {
    rotating = true;
  }
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() + getScaledHeight() > worldHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() + getScaledWidth() > worldWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
  if ( rotating ) {
    angle += std::max(1.0, 1.0*ticks/rotateSpeed);
    if ( angle > 360 ) {
      rotating = false;
      angle = 0.0f;
    }
  }

}
