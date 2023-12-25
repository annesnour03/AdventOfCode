#include "../helper.h"

std::vector<int> get_derivative(std::vector<int> in) {
    std::vector<int> out;

    std::transform(in.begin(), in.end() - 1, in.begin() + 1,
                   std::back_inserter(out),
                   [](int a, int b) { return b - a; });
    return out;
}

int solve_line(std::vector<int>& line) {
    std::vector<std::vector<int>> tmp;
    std::reverse(line.begin(), line.end());
    tmp.push_back(line);

    auto deriv = get_derivative(line);

    while (!std::all_of(deriv.begin(), deriv.end(), [](int i) { return i == 0; })) {
        tmp.push_back(deriv);
        deriv = get_derivative(deriv);
    }

    tmp.push_back(deriv);
    std::reverse(tmp.begin(), tmp.end());
    for (size_t i = 1; i < tmp.size(); ++i) {
        auto& row = tmp[i];
        row.push_back(tmp[i - 1].back() + row.back());
    }
    return tmp.back().back();
}

int solve(std::vector<std::vector<int>> input) {
    int res = 0;
    for (auto line : input)
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
    std::vector<std::vector<int>> parsed_data;
    while (std::getline(file, line)) {
        std::stringstream iss(line);
        int num;
        std::vector<int> res;
        while (iss >> num)
            res.push_back(num);
        parsed_data.push_back(res);
    }
    cout << solve(parsed_data) << endl;
    return 0;
}