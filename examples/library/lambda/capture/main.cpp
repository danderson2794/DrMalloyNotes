#include <iostream>
#include <functional>
#include <ctime>

// [capture clause] (parameters) -> return-type {body}
int y = 100;

int main() {
  int x = 5;
  constexpr int z = 2;

  std::function<void(int&)> triple = [](int& x) { x *= 3; };
  triple(x);
  std::cout << x << std::endl;

  auto f = [&x]() { x *= 3; };
  f();
  std::cout << x << std::endl;

  auto g = []() { y *= 3; };
  g();
  std::cout << y << std::endl;

  auto h = []() { std::cout << z << std::endl; };
  h();
}
