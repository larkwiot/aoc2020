#include "../lib/util.h"

std::vector<std::vector<char>> make_grid(std::vector<std::string>& lines) {
    std::vector<std::vector<char>> grid {};
    
    for (auto l : lines) {
        std::vector<char> row {};

        for (auto c : l) {
            row.push_back(c);
        }

        grid.push_back(row);
    }

    return grid;
}

bool solve(std::string fn) {
    auto lines = read_file_lines(fn);
    auto grid = make_grid(lines);

    int right = 3;
    int down = 1;

    int width = grid[0].size();

    int y = 0;
    int x = 0;

    int trees = 0;

    // iterate over every row
    while (y < grid.size()) {
        if (grid[y][x] == '#') {
            trees++;
        }

        y += down;
        x += right;
        x %= width;
    }

    std::cout << "[-] finish: found #" << trees << "\n";

    return true;
}