//
// Created by me on 12/2/20.
//

#include "../lib/util.h"

#ifndef AOC2020_PART2_H
#define AOC2020_PART2_H

template <typename I>
bool solve(std::string fn, I target) {
    auto nums = read_file_nums(fn);
    //std::cout << "read " << nums.size() << " lines\n";
    std::sort(nums.begin(), nums.end());
    for (I j = 0, sz = nums.size(); j < (sz - 1); ++j) {
        auto p = nums.at(j);

        for (I i = 1, sz = nums.size(); i < (sz - 1); ++i) {
            auto n = nums.at(i);

            if (n > target) {
                continue;
            }

            I bottom = i + 1;
            I top = sz - 1;
            I ptr = ((top - bottom) / 2) + bottom;
            I other = nums.at(ptr);
            I sum = p + n + other;

            while (sum != target && (top - bottom) > 1) {
                //std::cout << bottom << "-" << ptr << "-" << top << "\n";
                //std::cout << n << " + " << other << " = " << sum << "\n";
                if (sum > target) {
                    top = ptr;
                } else {
                    bottom = ptr;
                }

                ptr = ((top - bottom) / 2) + bottom;
                other = nums.at(ptr);
                sum = p + n + other;
            }

            if (sum == target) {
                std::cout << "[f] Found trio! " << p << " " << n << " " << other << "\n";
                std::cout << "[a] Answer = " << p * n * other << "\n";
                return true;
            } else if (n + nums.at(top) == target) {
                std::cout << "[f] Found trio! " << p << " " << n << " " << nums.at(top) << "\n";
                std::cout << "[a] Answer = " << p * n * nums.at(top) << "\n";
                return true;
            } else {
                continue;
            }
        }
    }

    return false;
}

#endif //AOC2020_PART2_H
