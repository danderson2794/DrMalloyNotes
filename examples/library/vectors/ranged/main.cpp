// 1. How does size and capacity grow?
// 2. reserve
// 3. Use a ranged for-loop to write display(vec)
// 4. Erase all of the even numbers in the vector

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vector>
const int MAX = 10;

void display(const std::vector<int> vec) {
  for (int i : vec) {
    std::cout << i << "   ";
  }
  std::cout << std::endl;
}

int main() {
  srand( time(0) );
  std::vector<int> vec;
  for (int i = 0; i < MAX; ++i) {
    vec.push_back( rand() );
  }
  std::cout << vec.size() << ", " << vec.capacity() << std::endl;
  display( vec );
}
