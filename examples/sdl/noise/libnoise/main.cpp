#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <noise.h>

using namespace noise;

int main (int, char**)
{
  module::Perlin myModule;
  double value = myModule.GetValue (1.25, 0.75, 0.50);
  std::cout << value << std::endl;
  return 0;
}
