#include <iostream>
#include <cstring>
#include <vector>

class string {
public:
  string() : buf(new char[1]) {
    std::cout << "default" << std::endl;
    buf[0] = '\0';
  }
  string(const char* s) : buf(new char[strlen(s)+1]) {
    std::cout << "convert" << std::endl;
    strcpy(buf, s);
  }
  explicit string(const string& s) : buf(new char[strlen(s.buf)+1]) {
    std::cout << "copy" << std::endl;
    strcpy(buf, s.buf);
  }
  ~string() { 
    std::cout << "destructor" << std::endl;
    delete [] buf; 
  }

  string& operator=(const string& rhs) {
    std::cout << "copy assign" << std::endl;
    if ( this == &rhs ) return *this;
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    return *this;
  }

  const char* getBuf() const { return buf; }

private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

int main() {
  std::vector<string> vec;
  for (unsigned int i = 0; i < 2; ++i) {
    vec.push_back(string());
  }
}
