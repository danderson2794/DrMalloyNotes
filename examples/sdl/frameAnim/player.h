#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "bullets.h"

class CollisionStrategy;
class ExplodingSprite;

class Player : public Drawable {
public:
  Player(const std::string&);
  virtual ~Player();

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void shoot();
  virtual bool gotShot(const Drawable*) const;
  virtual void explode();
  virtual bool collidedWith(const Drawable*);

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

  void right();
  void left();
  void up();
  void down();
  void stop();

  Player(const Player&) = default;
  Player& operator=(const Player&) = default;

private:
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  Vector2f initialVelocity;

  CollisionStrategy* collisionStrategy;
  ExplodingSprite* explosion;

  std::string bulletName;
  Bullets bullets;
  float bulletSpeed;
  int bulletInterval;
  int timeSinceLastBullet;

  void advanceFrame(Uint32 ticks);
};
#endif
