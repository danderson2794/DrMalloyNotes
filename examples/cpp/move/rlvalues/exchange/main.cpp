#include <iostream>
#include <utility>

int main() {
  int x = 17, y = 21, z = 29;
  z = std::exchange(x, 0);
  std::cout << "x is " << x << std::endl;
  std::cout << "y is " << y << std::endl;
  std::cout << "z is " << z << std::endl;

  x = 17, y = 21, z = 29;
  z = std::exchange(x, y);
  std::cout << "x is " << x << std::endl;
  std::cout << "y is " << y << std::endl;
  std::cout << "z is " << z << std::endl;
}
