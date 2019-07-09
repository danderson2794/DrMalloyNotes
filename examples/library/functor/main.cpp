#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Number {
public:
  Number(int n) : number(n) {}
  int getNumber() const { return number; }
  bool operator<(const Number& rhs) const {
    return number < rhs.number;
  }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number* n) {
  return out << n->getNumber();
}

// Function Object (functor)
class LessThan {
public:
  bool operator()(const Number* lhs, const Number* rhs) const {
    return lhs->getNumber() < rhs->getNumber();
  }
};

int main() {
  // Lambda Function:
  std::function<void(const Number*)> display = [](const Number* x) { 
    std::cout << x << std::endl; 
  };
  std::vector<Number*> vec = { 
    new Number(rand()%100), 
    new Number(rand()%100), 
    new Number(rand()%100) };
  std::for_each(vec.begin(), vec.end(), display);
  std::sort(vec.begin(), vec.end(), LessThan());
  std::for_each(vec.begin(), vec.end(), display);
}
