#include <iostream>

class Pokemon {
public:
  Pokemon(int c) : cp(c) {
    ++count;
  }
  int getCP() const { return cp; }
  static int getCount() { return count; }
private:
  int cp;
  static int count;
};
std::ostream& operator<<(std::ostream& out, const Pokemon& p) {
  return out << p.getCP();
}

void fun() {
  int x = 0;
  static int y = 0;
  ++x; ++y;
  std::cout << x << std::endl;
  std::cout << y << std::endl;
}

int Pokemon::count = 0;

int main() {
  fun();
  fun();
  Pokemon snorlax(1000), blissy(2500), feebas(0);
  std::cout << Pokemon::getCount() << std::endl;
  Pokemon* ptr = new Pokemon(88);
  std::cout << *ptr << std::endl;
  if ( dynamic_cast<Pokemon*>(ptr) ) {
    std::cout << "It's a poke" << std::endl;
  }
  delete ptr;
}
