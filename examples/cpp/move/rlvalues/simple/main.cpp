#include <iostream>

int f() { return 7; }

void f(int& a) { std::cout << "l-value ref: " << a<< std::endl; }
void f(int&& x) { std::cout << "r-value ref: " <<x<< std::endl; }

int main() {
  int x = 0;
  int* p = & x;
  f(x);
  f(std::move(x));
  f(x+1);
  f(f());
}
