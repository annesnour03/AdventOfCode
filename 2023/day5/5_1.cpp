#include <map>

#include "../helper.h"

long long get_dest(std::vector<std::string> lines, long long n) {
    auto f = [](std::string seq) -> std::tuple<long long, long long, long long> {
        std::vector<long long> res;
        std::stringstream iss(seq);
        long long num;
        while (iss >> num)
            res.push_back(num);

        return {res[0], res[1], res[2]};
    };
    for (auto line : lines) {
        std::tuple<long long, long long, long long> seq = f(line);

        long long destination_start = std::get<0>(seq);
        long long source_start = std::get<1>(seq);
        long long range_len = std::get<2>(seq);
        // check if within range
        if (n >= source_start && n <= source_start + range_len) {
            long long diff = n - source_start;
            return destination_start + diff;
        }
    }
    return n;
}
long long solve(std::vector<std::string> input) {
    long long res = 0;
    auto f = [](std::string seq) -> std::vector<long long> {
        std::vector<long long> res;
        std::stringstream iss(seq);
        long long num;
        while (iss >> num)
            res.push_back(num);

        return res;
    };

    std::vector<long long> seeds = f(input[0].substr(6));
    input.erase(input.begin());
    std::vector<std::vector<std::string>> sections;

    for (size_t i = 0; i < input.size(); i++) {
        std::string row = input[i];
        long long end = input.size();
        long long j = i + 1;
        if (std::isalpha(row[0])) {
            while (j < input.size() && std::isdigit(input[j][0]))
                j++;
        }
        std::vector<std::string> sub(&input[i + 1], &input[j]);
        sections.push_back(sub);
    }
    auto min_dest = [&sections](long long seed) {
        long long current = seed;
        for (auto section : sections) {
            current = get_dest(section, current);
        }
        return current;
    };

    long long cur_min = __LONG_LONG_MAX__;
    for (auto seed : seeds)
        cur_min = std::min(cur_min, min_dest(seed));
    return cur_min;
}
int main(long long argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::string> parsed_data;
    while (std::getline(file, line)) {
        if (line.size()) {
            parsed_data.push_back(line);
        }
    }
    cout << solve(parsed_data) << endl;
    return 0;
}