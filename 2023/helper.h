#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
using std::cout;
using std::endl;

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

template <typename Out>
void split(const std::string &s, const std::string &delim, Out result) {
    size_t start = 0, end = 0;
    while ((end = s.find(delim, start)) != std::string::npos) {
        *result++ = s.substr(start, end - start);
        start = end + delim.length();
    }
    *result++ = s.substr(start);
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<std::string> split(const std::string &s, const std::string &delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string unique(std::string s) {
    std::string str;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        size_t found = str.find(c);
        if (found == std::string::npos) {
            str += c;
        }
    }
    return str;
}

std::string join(const std::vector<std::string>& lst, const std::string& delim) {
    std::string ret;
    for (const auto& s : lst) {
        if (!ret.empty())
            ret += delim;
        ret += s;
    }
    return ret;
}

int char_2_int(char c) { return c - '0'; }
