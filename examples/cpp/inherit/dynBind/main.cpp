#include <iostream>

class Shape {
public:
  virtual void display() const {
    std::cout << "I'm a shape" << std::endl;
  }
};

class Circle : public Shape {
public:
  virtual void display() const {
    std::cout << "I'm a circle" << std::endl;
  }
};

class Rectangle : public Shape {
public:
  virtual void display() const {
    std::cout << "I'm a rectangle" << std::endl;
  }
};

int main() {
  srand( time(0) );
  Shape* shape = nullptr;
  shape = (rand() % 2) ? static_cast<Shape *>(new Rectangle) : static_cast<Shape *>(new Circle);
  shape->display();
}
