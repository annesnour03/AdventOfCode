#include <map>

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
    return res_array.size();
}

int solve(std::vector<std::string> input) {
    int res = 0;
    std::map<int, int> multipliers;
    int game_id = 0;
    for (size_t i = 0; i < input.size(); i++) {
        const std::string line = input[i];
        game_id = std::stoi(split(line, ':')[0].substr(5));

        int n_won = solve_line(line);
        for (size_t j = 0; j < n_won; j++) {
            int n = multipliers[j + game_id + 1];
            multipliers[j + game_id + 1] = n + multipliers[game_id] + 1;
        }
    }

    for (size_t n = 1; n <= game_id; n++) {
        res += multipliers[n] + 1;
    };
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