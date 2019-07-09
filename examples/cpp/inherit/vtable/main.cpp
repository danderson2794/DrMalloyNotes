#include <iostream>

class Empty {
  virtual ~Empty() {}
};

int main() {
  std::cout << sizeof( Empty ) << std::endl;
}
