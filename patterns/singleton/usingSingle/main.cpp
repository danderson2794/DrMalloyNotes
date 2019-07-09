#include <iostream>
#include <limits>
#include "random.h"

class Number{
public:
  Number() : number(Random::getInstance()(1,100)) { ++count; }
  Number(int n) : number(n) { ++count; }
  Number(const Number& n) : number(n.number) { ++count; }
  int getNumber() const { return number; }
  static int getCount() { return count; }
private:
  int number;
  static int count;
};

int Number::count = 0;

int main() {
  Number a, b;
  std::cout << "a's number is: " << a.getNumber() << std::endl;
  std::cout << "b's number is: " << b.getNumber() << std::endl;
  std::cout << "count is: " << Number::getCount() << std::endl;
}
