#include "../lib/util.h"

int compute_range(std::string str, char b, int diff) {
    int i = 0;
    for (auto c : str) {
        diff /= 2;
        if (c == b) {
            i += diff;
        }
    }
    return i;
}

int compute_id(std::string pass) {
    std::string row = pass.substr(0, 7);
    std::string col = pass.substr(7);
    
    int nrow = compute_range(row, 'B', 128);
    int ncol = compute_range(col, 'R', 8);

    return (nrow * 8) + ncol;
}

bool solve(std::string fn) {
    auto lines = read_file_lines(fn);

    std::sort(lines.begin(), lines.end());

    std::unordered_set<int> ids {};

    for (auto l : lines) {
        ids.emplace(compute_id(l));
    }

    int max_id = *(std::max_element(ids.begin(), ids.end()));

    std::cout << "[-] finish: max id: " << max_id << "\n";

    return true;
}