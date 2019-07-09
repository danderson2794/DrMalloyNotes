#include <string>
#include <iostream>

#include "multisprite.h"

class Dyingcrow : public MultiframeSprite {
public:
  Dyingcrow(const std::string&, const std::vector<Frame*>&);
  Dyingcrow(const Dyingcrow& s);
  virtual ~Dyingcrow() { } 
  Dyingcrow& operator=(const Dyingcrow&);
  virtual void update(Uint32 ticks);
  bool isDead() const { return dead; }

private:
  bool dead;
  float timeSinceLastFrame;
  int crowInterval;
  void advanceFrame(Uint32 ticks);
};
