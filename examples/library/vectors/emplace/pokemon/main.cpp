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
  string(string&& s) : buf(std::move(s.buf)) {
    s.buf = nullptr;
    std::cout << "move string" << std::endl;
  }
  ~string() { 
    delete [] buf;
    std::cout << "destructor string" << std::endl;
  }

  const char* getBuf() const { return buf; }
  string& operator=(string&& rhs) {
    buf = std::move(rhs.buf);
    rhs.buf = nullptr;
    return *this;
  }
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

class Pokemon {
public:
  Pokemon(const char* n) : name(n) { 
    std::cout << "convert mon" << std::endl;
  }
  Pokemon(const char* n, int, char) : name(n) { 
    std::cout << "complex mon" << std::endl;
  }
  Pokemon(const Pokemon& n) : name(n.name) {
    std::cout << "copy mon" << std::endl;
  }
  Pokemon(Pokemon&& n) : name(std::move(n.name)) {
    std::cout << "move mon" << std::endl;
  }
  const string& getName() const { return name; }
private:
  string name;
};

int main() {
  std::vector<Pokemon> mon;
  mon.emplace_back("mewtwo", 5, 'x');
}
