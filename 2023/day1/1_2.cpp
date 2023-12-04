#include <map>

#include "../helper.h"
bool is_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
std::string convert_line(std::string line) {
    std::map<std::string, std::string> numbers{
        {"one", "o1e"},
        {"two", "t2o"},
        {"three", "t3e"},
        {"four", "f4r"},
        {"five", "f5e"},
        {"six", "s6x"},
        {"seven", "s7n"},
        {"eight", "e8t"},
        {"nine", "n9e"}};
    std::vector<std::string> vints;
    for (auto const& imap : numbers)
        vints.push_back(imap.first);
    std::string copied = line;
    const int MAX = 5;
    for (int i = 0; i < copied.length(); i++) {
        auto substr = copied.substr(i, MAX);
        for (auto possible : numbers) {
            int idx = substr.find(possible.first);
            if (idx != -1)
                copied.replace(idx + i, possible.first.length(), (possible.second));
        }
    }
    return copied;
}
int solve(std::vector<std::string> input) {
    int res = 0;
    std::vector<std::string> collect;
    for (std::string var : input) {
        std::string copied = var;
        collect.push_back(convert_line(copied));
    }
    const std::string ALL = "0123456789";
    for (auto line : collect) {
        res += atoi((std::string() +
                     line.at(line.find_first_of(ALL)) +
                     line.at(line.find_last_of(ALL)))
                        .c_str());
    }
    return res;
}
int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::string> parsed_data;
    while (std::getline(file, line)) {
        parsed_data.push_back(line);
    }
    cout << solve(parsed_data) << endl;
    return 0;
}