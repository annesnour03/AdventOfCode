#include <map>

#include "../helper.h"

int solve(std::vector<std::string> input) {
    int res = 0;
    std::string pattern = input[0];
    std::vector<int> dirs;

    input.erase(input.begin(), input.begin() + 2);

    std::map<std::string, std::tuple<std::string, std::string>> lookup;
    for (auto line : input) {
        auto portion = split(line, " = (");
        auto dest = split(portion[1], ", ");
        std::string left = dest[0];
        std::string right = dest[1];
        right.pop_back();
        lookup.emplace(portion[0], std::make_tuple(left, right));
    }
    auto copy = pattern;
    std::string current = "AAA";
    while (current != "ZZZ") {
        auto options = lookup[current];
        if (copy[res % pattern.size()] == 'R')
            current = std::get<1>(options);
        else
            current = std::get<0>(options);
        res++;
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