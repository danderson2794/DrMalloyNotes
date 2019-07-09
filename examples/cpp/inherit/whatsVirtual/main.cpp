#include <iostream>
#include <vector>
#include <string>

class Base {
public:
  virtual ~Base() {}
  void f()         const { std::cout << "Base::f" << std::endl; }
  virtual void g() const { std::cout << "Base::g" << std::endl; }
  virtual void h() const = 0;
};
void Base::h() const { std::cout << "Base::h" << std::endl; }

class Derived : public Base {
public:
  virtual ~Derived() {}
  void f()         const { std::cout << "Derived::f" << std::endl; }
  virtual void g() const { std::cout << "Derived::g" << std::endl; }
  virtual void h() const { std::cout << "Derived::h" << std::endl; }
  void callH() { Base::h(); }
};

int main() {
  Base* obj = new Derived;
  obj->f();
  obj->g();
  obj->h();

  Derived x;
  x.f();
  x.callH();
}
