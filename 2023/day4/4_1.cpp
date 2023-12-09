#include "../helper.h"

int solve_line(const std::string& line) {
    std::string content = split(line, ':')[1];
    std::string winning = split(content, '|')[0];
    std::string scratched = split(content, '|')[1];
    auto f = [](std::string seq) -> std::set<int> {
        std::set<int> res;
        std::stringstream iss(seq);
        int num;
        while (iss >> num) {
            res.insert(num);
        }
        return res;
    };
    auto winning_numbers = f(winning);
    auto numbers = f(scratched);
    std::vector<int> res_array;
    std::set_intersection(winning_numbers.begin(), winning_numbers.end(),
                          numbers.begin(), numbers.end(),
                          std::back_inserter(res_array));
    return std::max(0.0, std::pow(2, res_array.size() - 1));
}

int solve(std::vector<std::string> input) {
    int res = 0;
    for (const std::string& line : input)
        res += solve_line(line);
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