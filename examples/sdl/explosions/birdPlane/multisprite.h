#ifndef MULTISPRITE__H
#define MULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "drawable.h"

class MultiframeSprite : public Drawable {
public:
  MultiframeSprite(const std::string& n, const std::vector<Frame*>& fms);
  MultiframeSprite(const string&);
  MultiframeSprite(const MultiframeSprite& s);
  virtual ~MultiframeSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { return frames[currentFrame]; }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  int frameWidth;
  int frameHeight;

  virtual void advanceFrame(Uint32 ticks);
};
#endif
