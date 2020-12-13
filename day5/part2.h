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

bool cmp_char(const char lhs, const char rhs) {
    static std::string ab = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static std::string tr = "ABCDEFGHIJKRMNOPQLSTUVWXYZ";
    
    auto lhs_tr = tr[ab.find(lhs)];
    auto rhs_tr = tr[ab.find(rhs)];

    return lhs_tr < rhs_tr;
}

bool cmp_str(const std::string& lhs, const std::string& rhs) {
    bool result = std::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        cmp_char    
    );

    return result;
}

bool solve(std::string fn) {
    auto lines = read_file_lines(fn);

    std::sort(lines.begin(), lines.end(), cmp_str);

    int max_id = compute_id(*(lines.begin()));
    //int min_id = compute_id(*(lines.rbegin()));

    int top = lines.size();
    int bot = 0;
    int test = ((top - bot) / 2) + bot;

    while ((top - bot) > 1) {
        //std::cout << "top: " << top << " bot: " << bot << " test: " << test << "\n";
        int test_id = compute_id(lines.at(test));
        int expected_id = max_id - test;
        //std::cout << test << " -> " << test_id << " w " << expected_id;
        if (test_id == expected_id) {
            //std::cout << " too low\n";
            bot = test;
        } else {
            //std::cout << " too high\n";
            top = test;
        }
        test = ((top - bot) / 2) + bot;
    }

    // I think this should always work...
    int my_seat_id = compute_id(lines.at(top)) + 1;

    std::cout << "[-] finish: my seat id: " << my_seat_id << "\n";

    return true;
}