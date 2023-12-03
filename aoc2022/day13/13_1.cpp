#include <variant>

#include "../helper.h"

struct PacketPair {
    int idx;
    std::string left;
    std::string right;
};
typedef std::variant<int, std::vector<int>> intOrVecInt;

int solve(std::vector<PacketPair> input) {
    int res = 0;
    return res;
}
bool checkIfInt(intOrVecInt my_variant) {
    return std::holds_alternative<int>(my_variant);
}

int getInt(intOrVecInt my_variant) {
    return std::get<int>(my_variant);
}

std::vector<int> getVecInt(intOrVecInt my_variant) {
    return std::get<std::vector<int>>(my_variant);
}

std::vector<intOrVecInt> parseLine(std::string in) {
    // Remove the first and last bracket.
    cout <<"size in" << in.size() <<endl;
    in.pop_back();
    in.erase(in.begin());
    const char COMMA = ',';
    const char START_BRACKET = '[';
    const char END_BRACKET = ']';
    std::vector<intOrVecInt> out;

    for (char c : in) {
        if (isdigit(c)) {
            out.push_back({c});
            cout << c << endl;
        }
        if(c == START_BRACKET){
            cout << "START BRACKET" << endl;
        }
        else if(c == END_BRACKET) {
            cout << "END BRACKET" << endl;
        }
    }
    return out;
}

int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<PacketPair> packet_pairs;
    int i = 0;
    while (std::getline(file, line)) {
        if (line.length() == 0)
            continue;
        std::string right;
        std::getline(file, right);
        packet_pairs.push_back({++i, line, right});
    }
    std::vector<intOrVecInt> my_value;
    // We parse the pairs.
    parseLine(packet_pairs[1].left);
    // cout
        // << solve(packet_pairs) << endl;
    return 0;
}