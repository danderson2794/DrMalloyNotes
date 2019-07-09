#include <iostream>
#include <vector>
#include <cstring>

class string {
public:
  string() { std::cout << "default" << std::endl;
  }
  string(const char *) { std::cout << "convert" << std::endl; }
  string(const string &) { std::cout << "copy" << std::endl; }
  string(const volatile string &) { std::cout << "copy" << std::endl; }
  ~string() { std::cout << "destructor" << std::endl; }
  string& operator=(const string&) {
    std::cout << "copy assign" << std::endl;
    return *this;
  }

  //string(string &&) { std::cout << "move constr" << std::endl; }
  //string& operator=(string&&) {
    //std::cout << "move assign" << std::endl;
    //return *this;
  //}
};

//#pragma GCC push_options
//#pragma GCC optimize "-fno-elide-constructors"
string noNRVO() {
  string s;
  return s;
}
//#pragma GCC pop_options

string nrvo2(string s) {
  s = "dog";
  return s;
}

string nrvo1() {
  string s;
  return s;
}

string rvo() {
  return string();
}

int main() {
  //string dummy = noNRVO();
  string dummy = rvo();
}
