#include "../helper.h"

bool nearest_star(int row, int col, const std::vector<std::string>& input) {
    if (input[row][col] == '.') return false;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newCol = col + i;
            int newRow = row + j;

            if (newRow >= 0 && newRow < input.size() && newCol >= 0 && newCol < input[0].size()) {
                char adjacentSymbol = input[newRow][newCol];
                if (adjacentSymbol != '.' && !isdigit(adjacentSymbol)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int solve(std::vector<std::string> input) {
    int res = 0;
    for (size_t row = 0; row < input.size(); row++) {
        std::string currentNumber;
        std::string currentRow = input[row];
        for (size_t col = 0; col < currentRow.size(); col++) {
            char current = currentRow[col];
            if (isdigit(current))
                currentNumber.push_back(current);
            else {
                if (currentNumber.size() > 0) {
                    bool is_nearby = nearest_star(row, col - 1, input);
                    for (size_t i = 2; i <= currentNumber.size(); i++)
                        is_nearby = is_nearby || nearest_star(row, col - i, input);

                    if (is_nearby)
                        res += std::stoi(currentNumber);
                    currentNumber.erase();
                }
            }
        }

        if (currentNumber.size() > 0) {
            bool is_nearby = nearest_star(row, currentRow.size() - 1, input);
            for (size_t i = 2; i <= currentNumber.size(); i++)
                is_nearby = is_nearby || nearest_star(row, currentRow.size() - i, input);

            if (is_nearby) {
                res += std::stoi(currentNumber);
                currentNumber.erase();
            }
        }
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