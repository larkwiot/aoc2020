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

    std::vector<std::pair<int, int>> steps {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2},
    };

    std::vector<int> trees_collection {};

    int width = grid[0].size();

    for (auto p : steps) {
        int right = p.first;
        int down = p.second;

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

        std::cout << "[i] found #" << trees << "\n";
        trees_collection.push_back(trees);
    }

    long solution = 1;
    for (auto x : trees_collection) {
        solution *= x;
    }

    std::cout << "[-] finish: product is " << solution << "\n";

    return true;
}