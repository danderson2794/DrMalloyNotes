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

A fun() { 
  std::cout << "nrvo" << std::endl;
  return A(); 
}

A fun(A&&) { 
  std::cout << "r-value reference" << std::endl;
  return A(); 
}
A fun(A&) { 
  std::cout << "l-value reference" << std::endl;
  std::cout << "nrvo" << std::endl;
  return A(); 
}

void f() { std::cout << "In function f" << std::endl; }
void intf(int& x) { std::cout << "In f by ref: " <<x<< std::endl; }
void intf(int&& x) { std::cout << "In f by r-value ref: " <<x<< std::endl; }

int main() {
  std::cout << "ONE" << std::endl;
  A&& f();
  A&& z = A();
  int&& x = 17+1;
  intf(x);

  std::cout << "TWO" << std::endl;
  A a;
  fun(a);
  std::cout << "THREE" << std::endl;
  fun(f());
  std::cout << "FOUR" << std::endl;
  fun(std::move(z));  // w/out std::move it's l-value reference

  std::cout << "FIVE" << std::endl;
  fun();
}
