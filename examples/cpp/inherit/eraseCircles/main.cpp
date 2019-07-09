#include <iostream>
#include <vector>
#include <string>

class Shape {
public:
  Shape(const std::string& n) : name(n) {}
  virtual ~Shape() {
    std::cout << "Shape Destr" << std::endl;
  }
  const std::string& getName() const { return name; }
  virtual float area() const = 0;
private:
  std::string name;
};

class Rectangle : public Shape {
public:
  Rectangle(const std::string& n, float w, float h) : 
    Shape(n), width(w), height(h) {}
  virtual ~Rectangle() {
    std::cout << "Rectangle Destr" << std::endl;
  }
  virtual float area() const { return width*height; } 
private:
  float width;
  float height;
};

class Triangle : public Shape {
public:
  Triangle(const std::string& n, float w, float h) : 
    Shape(n), base(w), height(h) {}
  virtual ~Triangle() {
    std::cout << "Triangle Destr" << std::endl;
  }
  virtual float area() const { return 0.5*base*height; } 
private:
  float base;
  float height;
};

void deleteTriangles(std::vector<Shape*>& shapes) {
  std::vector<Shape*>::const_iterator it = shapes.cbegin();
  while ( it != shapes.cend() ) {
    Triangle* t = dynamic_cast<Triangle*>(*it);
    if ( t ) {
      delete *it;
      it = shapes.erase(it);
    }
    else ++it;
  }
}

void printAreas(const std::vector<Shape*>& shapes) {
  for ( const Shape* const s : shapes ) {
    std::cout << s->area() << std::endl;
  }
}

int main() {
  std::vector<Shape*> shapes;
  shapes.push_back( new Rectangle("rectangle", 5.0, 7.2) );
  shapes.push_back( new Triangle("triangle", 25.0, 7.2) );
  shapes.push_back( new Rectangle("rectangle", 5.0, 17.2) );
  shapes.push_back( new Triangle("triangle", 75.0, 7.2) );
  printAreas(shapes);
  deleteTriangles(shapes);
  printAreas(shapes);
  auto it = shapes.begin();
  while ( it != shapes.end() ) {
    delete *it;
    ++it;
  }
}
