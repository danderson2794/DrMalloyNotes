#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

// [capture clause] (parameters) -> return-type {body}

class Multiple {
public:
  Multiple(int m) : mult(m) {}
  void operator()(int& x) const { x *= 4; }
private:
  int mult;
};

int main() {
  auto triple = [](int& x) { x *= 3; };
  auto print =  [](int x) { std::cout << x << "   "; };
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::for_each(vec.begin(), vec.end(), triple);
  std::for_each(vec.begin(), vec.end(), print);
  std::for_each(vec.begin(), vec.end(), Multiple(4));
  std::for_each(vec.begin(), vec.end(), Multiple(5));
  std::for_each(vec.begin(), vec.end(), print);
}
