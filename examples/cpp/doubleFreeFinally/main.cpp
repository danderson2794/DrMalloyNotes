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
  string& operator=(const string&);
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

string& string::operator=(const string& s) {
  if ( this == &s ) return *this;
  delete [] buf;
  buf = new char[strlen(s.buf)+1];
  strcpy(buf, s.buf);
  return *this;
}

int main() {
  string a("dog"), b = a;
  b.operator=(a);
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  //std::cout << (b+a) << std::endl;
}
