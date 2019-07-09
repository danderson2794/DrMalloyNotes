#include "random.h"

Random::Random() { 
  int seed = time(0);
  srand(seed); 
}

Random& Random::getInstance() {
  static Random instance;
  return instance;
}

