#include <iostream>

class Pokemon {
public:
  Pokemon(int c = 0) : cp(c) {}
  int getCp() const { return cp; }
private:
  int cp;
};
std::ostream&  operator<<(std::ostream& out, const Pokemon& p) {
  return out << p.getCp();
}

int main() {
  Pokemon snorlax, blissy(2700);
  std::cout << "snorlax is " << snorlax  << std::endl;
  std::cout << "blissy is " << blissy  << std::endl;
}
