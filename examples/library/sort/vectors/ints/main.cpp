
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

class Number {
public:
  Number(int n) : number(n) {}
  bool operator<(const Number& n) const {
    if(number < n.number) 
      {return true;} 
    else 
      {return false;}
  }
  int getNumber() const { return number; }
private:
  int number;
};

class FuncObj {
public:
   bool operator()(const Number* lhs, const Number* rhs) const {
      return (*lhs) < (*rhs);
   }
};

void init(std::vector<Number*> & vec) {
  vec.reserve(MAX);
  for (unsigned int i = 0; i < MAX; ++i) {
    vec.push_back( new Number(rand() % MAX_NUMBER) );
  }
}

void print(const std::vector<Number*> & vec) {
  for ( const Number* number : vec ) {
    std::cout << number->getNumber()  << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<Number*> vec;
  init(vec);
  print(vec);
  // sort the stupid vector:
  std::sort(vec.begin(), vec.end(), FuncObj());
  print(vec);
}
