#include "../helper.h"

int solve(std::vector<std::string> input) {
    int res = 0;
    const std::string ALL = "0123456789";
    for (auto line : input) {
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