#include <iostream>

class A {
public:
  virtual ~A() {}
  void f() { std::cout << "I'm an f" << std::endl; }
};

class B : public A {
public:
  void g() { std::cout << "I'm an g" << std::endl; }
};

class C : public A {
public:
  C() : number(17) {}
  void j() { std::cout << "I'm an j" << std::endl; }
  int number;
};

int main() {
  A* x = new B;
  static_cast<B*>(x)->g();

  B* b = dynamic_cast<B*>(x);
  std::cout << b << std::endl;

  C* c = static_cast<C*>(x);
  c->j();
  std::cout << c->number << std::endl;
  c->number = 99;
  std::cout << c->number << std::endl;
}
