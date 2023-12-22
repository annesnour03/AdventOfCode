#include <map>

#include "../helper.h"

long long findlcm(std::vector<int> arr) {
    long long ans = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        long long tmp = static_cast<long long>(arr[i]) * ans;
        ans = tmp / std::gcd(arr[i], ans);
    }
    return ans;
}

long long solve(std::vector<std::string> input) {
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
    std::vector<std::string> all_current;
    std::transform(lookup.cbegin(), lookup.cend(), std::back_inserter(all_current),
                   [](const auto& kv_pair) {
                       const std::string& key = kv_pair.first;
                       if (key.size() >= 1 && key.back() == 'A') {
                           return key;
                       } else {
                           return std::string();
                       }
                   });

    // Remove empty strings from the vector
    all_current.erase(std::remove(all_current.begin(), all_current.end(), ""), all_current.end());
    auto is_end = [&all_current]() -> bool {
        return std::all_of(all_current.begin(), all_current.end(),
                           [](const std::string& str) {
                               return !str.empty() && str.back() == 'Z';
                           });
    };
    std::map<std::string, int> seen;

    int twice = 0;
    int c = 0;
    while (seen.size() < all_current.size()) {
        std::vector<std::string> next;
        for (auto state : all_current) {
            auto options = lookup[state];
            if (copy[c % pattern.size()] == 'R')
                next.push_back(std::get<1>(options));
            else
                next.push_back(std::get<0>(options));
        }
        for (auto var : all_current) {
            if (var.back() == ('Z')) {
                int noted = seen[var];
                seen[var] = c;
                twice++;
            }
        }
        all_current = next;
        c++;
    }
    std::vector<int> v;
    for (auto it = seen.begin(); it != seen.end(); ++it) {
        v.push_back(it->second);
    }

    return findlcm(v);
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