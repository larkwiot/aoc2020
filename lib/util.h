#include "includes.h"

#ifndef AOC2020_UTIL_H
#define AOC2020_UTIL_H

std::vector<long> read_file_nums(std::string fn) {
    std::ifstream fh {fn};
    auto lines = std::vector<std::string> {};

    std::copy(std::istream_iterator<std::string>(fh),
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    auto nums = std::vector<long> {};
    std::transform(lines.begin(), lines.end(), std::back_inserter(nums),
                   [](std::string s) { return std::stol(s); });

    return nums;
}

std::vector<std::string> read_file_lines(std::string fn) {
    std::ifstream fh {fn};

    if (!fh) {
        std::cerr << "[!] error: could not open " << fn << "\n";
        abort();
    }

    auto lines = std::vector<std::string> {};

    std::string l;
    while (std::getline(fh, l)) {
        lines.push_back(l);
    }
    
    return lines;
}

#endif //AOC2020_UTIL_H
