#include <iostream>
#include <vector>
#include <cstring>

const int MAX = 10;

class string {
public:
  string() : buf(new char[1]) {
    buf[0] = '\0';
  }
  string(const char* s) : buf(new char[strlen(s)+1]) {
    strcpy(buf, s);
  }
  string(const string& s) : buf(new char[strlen(s.buf)+1]) {
    strcpy(buf, s.buf);
  }
  ~string() { 
    delete [] buf; 
  }  // s/ destructors always be virtual

  string(string&& s) : buf(std::move(s.buf)) {
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

  //string& operator=(string&& rhs) {
    //std::cout << "move assignment" << std::endl;
    //std::swap(buf, rhs.buf);
    //return *this;
  //}
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}


void norvo(string& s) {
  s = "bat";
}

int main() {
  for ( int i = 0; i < MAX; ++i ) {
    string cat("cat");
    norvo(cat);
  }
}
