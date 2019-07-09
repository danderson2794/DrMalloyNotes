#include <iostream>
#include <vector>
#include <cstring>

class string {
public:
  string() : buf(new char[1]) { 
    buf[0] = '\0';
    std::cout << "default string" << std::endl;
  }
  string(const char * b) : buf(new char[strlen(b)+1]) {
    strcpy(buf, b);
    std::cout << "convert string" << std::endl;
  }
  string(const string & s) : buf(new char[strlen(s.buf)]) {
    strcpy(buf, s.buf);
    std::cout << "copy string" << std::endl;
  }
  ~string() { 
    delete [] buf;
    std::cout << "destructor string" << std::endl;
  }

  const char* getBuf() const { return buf; }
  string& operator=(const string& rhs) {
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    std::cout << "assign string" << std::endl;
    return *this;
  }
private:
  char *buf;
};
std::ostream& operator<<(std::ostream& out, const string& n) {
  return out << n.getBuf();
}

int main() {
  std::vector<string> mon;
  // emplace_back can be more efficient than move
  //mon.emplace_back("mewtwo");
  mon.push_back("mewtwo");
}
