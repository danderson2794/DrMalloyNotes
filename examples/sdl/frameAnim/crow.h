#pragma once

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "dyingSprite.h"

class CollisionStrategy;

class Crow : public Drawable {
public:
  Crow(const std::string&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual bool collidedWith(const Drawable*) {
    throw std::string("I don't collide: ")+getName();
  }

  virtual bool doneDying() const { 
    if ( deathAnim ) return deathAnim->doneDying();
    return false;
  }

  virtual void explode();

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }

  Crow(const Crow&) = default;
  Crow& operator=(const Crow&) = default;

protected:
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;
  std::vector<Image *> images;
  DyingSprite* deathAnim;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
};
