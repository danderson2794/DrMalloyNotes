#include <iostream>

class A{
public:
  A() { std::cout << "default constructor" << std::endl; }
  A(const A&) { std::cout << "copy constructor" << std::endl; }
  A(const A&&) { std::cout << "move constructor" << std::endl; }
  A& operator=(const A&) {
    std::cout << "copy assignment" << std::endl;
    return *this;
  }
  A& operator=(const A&&) {
    std::cout << "move assignment" << std::endl;
    return *this;
  }
};

A fun(A&&) { 
  std::cout << "r-value reference" << std::endl;
  return A(); 
}
A fun(A&) { 
  std::cout << "l-value reference" << std::endl;
  return A(); 
}

void f() { std::cout << "in f" << std::endl; }
void f(int& x)  { std::cout << "In f by l-value ref: " <<x<< std::endl; }
void f(int&& x) { std::cout << "In f by r-value ref: " <<x<< std::endl; }

int main() {
  std::cout << "*** 1 ***" << std::endl;
  int&& x = 17+1;
  f(x);
  std::cout << "*** 2 ***" << std::endl;

  A a;
  fun(a);
  std::cout << "*** 3 ***" << std::endl;
  A&& z = A();
  fun(z);
  std::cout << "*** 4 ***" << std::endl;
  fun(std::move(z));  // w/out std::move it's l-value reference
}
