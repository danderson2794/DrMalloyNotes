#include <cstdlib>  // for rand()
#include <iostream>
// GoF Singleton

class Random {
public:
  static Random* getInstance() {
    if ( !instance ) instance = new Random;
    return instance;
  }
  int operator()(int a, int b) const { 
    return (rand() % b) + a; 
  }
private:
  static Random* instance;
  Random(const Random&);
  Random& operator=(const Random&);
  Random() { 
    int seed = time(0);
    srand(seed); 
  }
};

Random* Random::instance = nullptr;

void printRandom() {
  std::cout << (*Random::getInstance())(1,100) << std::endl;
}

int main() {
  Random* random = Random::getInstance();
  std::cout << (*random)(1,100) << std::endl;
  printRandom();
  delete random;
}
