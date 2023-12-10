#include "../helper.h"

int solve(std::vector<std::string> input) {
    int res = 1;
    auto f = [](std::string seq) -> std::vector<int> {
        std::vector<int> res;
        std::stringstream iss(seq);
        int num;
        while (iss >> num)
            res.push_back(num);

        return res;
    };

    std::vector<int> time_limits = f(split(input[0], ':')[1]);
    std::vector<int> records = f(split(input[1], ':')[1]);

    for (size_t i = 0; i < records.size(); i++) {
        int limit = time_limits[i];
        int record = records[i];
        int cur_ways = 0;
        for (size_t time_pressed = 0; time_pressed < limit; time_pressed++) {
            int time_for_game = limit - time_pressed;
            int distance = time_for_game * time_pressed;
            if (distance > record) cur_ways++;
        }
        res *= cur_ways;
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