#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

// [capture clause] (parameters) -> return-type {body}

int main() {
  std::function<void(int&)> triple = [](int& x) { x *= 3; };
  int x = 5;
  triple(x);
  std::cout << x << std::endl;
}
