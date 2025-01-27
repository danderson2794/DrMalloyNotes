#include <iostream>
#include <cstring>

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
  string(const string& s) : buf(new char[strlen(s.buf)+1]) {
    std::cout << "copy" << std::endl;
    strcpy(buf, s.buf);
  }
  ~string() { 
    std::cout << "destruct" << std::endl;
    delete [] buf; 
  }  // s/ destructors always be virtual

  string(string&& s) : buf(std::move(s.buf)) {
    std::cout << "move constructor" << std::endl;
    s.buf = nullptr;
  }

  const char* getBuf() const { return buf; }

  string& operator=(const string& rhs) {
    std::cout << "copy assignment" << std::endl;
    if ( this == &rhs ) return *this;
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    return *this;
  }

  string& operator=(string&& rhs) {
    std::cout << "move assignment" << std::endl;
    // delete [] buf;
    // buf = std::move(rhs.buf);
    // rhs.buf = nullptr;
    std::swap(buf, rhs.buf);
    return *this;
  }
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

void print(string s) {
  std::cout << s << std::endl;
}

int main() {
  string dog;
  dog = "dog";
  std::cout << dog << std::endl;
  print( string("cat") );
}
