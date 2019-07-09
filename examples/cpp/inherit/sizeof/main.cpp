#include <iostream>

class Empty { };

int main() {
  int x = 7;
  long y = 7;
  Empty z;

  std::cout << sizeof(x) << std::endl;
  std::cout << sizeof(y) << std::endl;
  std::cout << sizeof(z) << std::endl;
  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(Empty) << std::endl;

  Empty* obj = new Empty;
  std::cout << sizeof(obj) << std::endl;
  std::cout << sizeof(*obj) << std::endl;
}
