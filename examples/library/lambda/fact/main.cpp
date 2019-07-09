#include <iostream>
#include <functional>
#include <ctime>

// [capture clause] (parameters) -> return-type {body}

int main() {
  std::function<int(int)> fact;
  fact = [&fact](int x) { 
    if( x==0 ) return 1; 
    else return x*fact(x-1);
  };
  std::cout << "fact(5) = " << fact(5) << std::endl;
}
