#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class Triple {
public:
  void operator()(int& x) { x *= 3; };
};

int main() {
  std::vector<int> vec = {1, 2, 3, 4, 5};

  std::function<void(int)> print = [](int x) { std::cout << x << "  "; };
  auto triple = [](int& x) { x *= 3; };

  for_each(vec.begin(), vec.end(), triple);
  for_each(vec.begin(), vec.end(), Triple());
  for_each(vec.begin(), vec.end(), print);
  std::cout << std::endl;
}
