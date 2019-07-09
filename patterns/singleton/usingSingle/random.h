#include <cstdlib>  // for rand()
#include <iostream>

class Random {
public:
  static Random& getInstance();
  int operator()(int a, int b) const { 
    return (rand() % b) + a; 
  }
private:
  Random(const Random&);
  Random& operator=(const Random&);
  Random();
};
