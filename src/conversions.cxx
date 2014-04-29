#include <sstream>
using namespace std;

string num2string(double v) {
    stringstream ss;
    ss << v;
    return ss.str();
}
string bool2string(bool v) {
    stringstream ss;
    ss << v;
    return ss.str();
}

