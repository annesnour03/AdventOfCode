#include "../helper.h"

typedef enum CellTypes {
    AIR,
    ROCK,
    SAND,
} CellTypes;

struct Point {
    int x, y;

    friend std::ostream &operator<<(std::ostream &os, const Point value) {
        os << "(" << value.x << ", " << value.y << ")";
        return os;
    }
};

int solve(std::vector<std::string> input) {
    int res = 0;
    return res;
}

void initialise_grid(std::vector<std::vector<CellTypes>> &grid, std::vector<std::vector<Point>> points) {
    for (std::vector<Point> point_line : points) {
        for (Point point : point_line) {
            cout << point.x << " " << point.y << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::vector<Point>> parsed_data;
    while (std::getline(file, line)) {
        if (line.length() == 0)
            continue;
        std::vector<std::string> a = split(line, ' -> ');
        std::vector<Point> path;
        for (auto coord : a) {
            std::vector<std::string> numbs = split(line, ',');
            path.push_back({std::stoi(numbs[0]), std::stoi(numbs[1])});
        }
        parsed_data.push_back(path);
    }

    std::vector<std::vector<CellTypes>> grid;
    cout << "size == " << parsed_data.size() << endl;
    initialise_grid(grid, parsed_data);

    // cout << solve(parsed_data) << endl;
    return 0;
}