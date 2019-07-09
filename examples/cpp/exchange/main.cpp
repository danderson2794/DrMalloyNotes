#include <iostream>
#include <utility>

int main() {
  int x = 99;
  int y = 17;
  int z = 0;
  z = std::exchange(x, y);

  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;
}
