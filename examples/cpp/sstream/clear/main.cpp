#include <iostream>
#include <sstream>
#include <string>

void test_sstream(int bug) {
    std::stringstream stream;
    stream<<"abc";
    std::cout << "stream is: " << stream.str() << std::endl;

    // We should use both clear() and str("")
    if(bug == 0) {
        stream.clear();//clear error flag
        stream.str("");//clear content
    }
    else if (bug == 1) {
        stream.clear();//clear error flag
    }
    else if (bug == 2) {
        stream.str("");//clear content
    }
    stream << "def";
    std::string s;
    stream>>s;
    std::cout << "BUG=" << bug << " DEF = " << s <<std::endl;
}
    
int main() {
    test_sstream(0);
    test_sstream(1);
    test_sstream(2);
}
