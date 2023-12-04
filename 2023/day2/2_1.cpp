#include <map>
#include <sstream>

#include "../helper.h"
int solve_line(std::string line) {
    std::map<std::string, int> numbers{
        {"red", 12},
        {"green", 13},
        {"blue", 14},
    };

    auto gameAndIns = split(line, ':');
    int gameId = std::stoi(gameAndIns[0].erase(0, 4));

    std::vector<std::string> colors = {"red", "green", "blue"};
    std::string ins = gameAndIns[1];
    for (std::string& color : colors) {
        std::vector<size_t> positions;
        size_t current = ins.find(color, 0);
        while (current != std::string::npos) {
            positions.push_back(current - 3);
            current = ins.find(color, current + 1);
        }
        for (const int& pos : positions) {
            if (pos != -1 && (std::stoi(ins.substr(pos, 2))) > numbers[color]) {
                return gameId;
            }
        }
    }
    return 0;
}
int solve(std::vector<std::string> input) {
    const int size = input.size();
    int res = size * (size + 1) / 2;
    for (auto line : input) {
        res -= solve_line(line);
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