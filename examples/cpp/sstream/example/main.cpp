#include <iostream>
#include <sstream>

int main() {
  std::string s;
  double x = 2.5;
  std::stringstream strm;
  strm << x;
  s = strm.str();
  std::cout << s << std::endl;
}
