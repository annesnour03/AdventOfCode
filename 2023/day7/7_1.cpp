#include <algorithm>
#include <map>

#include "../helper.h"

typedef enum Ranking : unsigned long long {
    FIVE_OF_KIND = 6,
    FOUR_OF_KIND = 5,
    FULL_HOUSE = 4,
    THREE_KIND = 3,
    TWO_PAIR = 2,
    ONE_PAIR = 1,
    HIGH_CARD = 0,
} Ranking;
std::map<char, int> mapping{
    {'A', 14},
    {'K', 13},
    {'Q', 12},
    {'J', 11},
    {'T', 10},
    {'9', 9},
    {'8', 8},
    {'7', 7},
    {'6', 6},
    {'5', 5},
    {'4', 4},
    {'3', 3},
    {'2', 2}};

Ranking get_ranks(std::string cards) {
    std::unordered_map<char, int> counter;
    for (char card : cards) {
        counter[card]++;
    }

    std::vector<int> counts;
    for (const auto& entry : counter) {
        counts.push_back(entry.second);
    }

    std::sort(counts.begin(), counts.end());

    if (counts == std::vector<int>{5}) return FIVE_OF_KIND;
    if (counts == std::vector<int>{1, 4}) return FOUR_OF_KIND;
    if (counts == std::vector<int>{2, 3}) return FULL_HOUSE;
    if (counts == std::vector<int>{1, 1, 3}) return THREE_KIND;
    if (counts == std::vector<int>{1, 2, 2}) return TWO_PAIR;
    if (counts == std::vector<int>{1, 1, 1, 2}) return ONE_PAIR;
    if (counts == std::vector<int>{1, 1, 1, 1, 1}) return HIGH_CARD;

    return HIGH_CARD;
}

long long get_score(std::string cards) {
    int rank = (int)get_ranks(cards);
    int score = 0;
    for (size_t i = 0; i < 5; i++) {
        char c = cards[i];
        int value = mapping[c];

        int place = 4 - i;
        score += value * std::pow(13, place);
    }
    return rank * std::pow(13, 5) + score;
}

int solve(std::vector<std::string> input) {
    long long res = 0;
    std::vector<std::pair<int, std::string>> scores;

    for (auto line : input) {
        std::string firstToken = split(line, ' ')[0];
        int score = get_score(firstToken);
        scores.emplace_back(score, line);
    }

    // Sort the scores based on the first element of the pair (the score)
    std::sort(scores.begin(), scores.end());

    for (size_t i = 0; i < scores.size(); i++) {
        int bid = std::stoi(split(scores[i].second, ' ')[1]);
        res += (i + 1) * bid;
    }

    for (auto score : scores) {
        cout << score.second << " " << score.first << endl;
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