#include <iostream>
#include <cstring>

class string {
public:
  string(const char* b) : buf(new char[strlen(b)+1]) {
    strcpy(buf, b);
  }
  ~string() { 
    delete [] buf; 
    std::cout << "destroy" << std::endl;
  }
  const char* getBuf() const { return buf; }
  string(const string&) = delete;
  string& operator=(const string&) = delete;
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

int main() {
  string a("dog"), b = a;
  std::cout << a << std::endl;
  //std::cout << (b+a) << std::endl;
}
