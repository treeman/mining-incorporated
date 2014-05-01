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
string trim(string s) {
    if (s.empty()) return s;

    int l = 0;
    while (l < (int)s.size() && s[l] == ' ')
        ++l;

    int r = s.size() - 1;
    while (r >= 0 && s[r] == ' ')
        --r;

    if (l > r) return "";

    string res;
    for (int i = l; i <= r; ++i)
        res.push_back(s[i]);
    return res;
}

