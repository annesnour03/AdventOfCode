#include "../helper.h"

int solve(std::vector<std::string> input) {
    auto f = [](std::string seq) -> long long {
        std::vector<long long> res;
        std::stringstream iss(seq);
        long long num;
        std::string tmp;
        while (iss >> num)
            tmp.append(std::to_string(num));
        return std::stol(tmp);
    };

    long long time_limit = f(split(input[0], ':')[1]);
    long long record = f(split(input[1], ':')[1]);
    double right = (time_limit + std::sqrt(std::pow(time_limit, 2) - 4 * record)) / 2;
    double left = (time_limit - std::sqrt(std::pow(time_limit, 2) - 4 * record)) / 2;
    return std::floor(right) - std::floor(left);
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