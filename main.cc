#include "lib/includes.h"
#include "day5/part1.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "[!] error: no file given!\n";
        abort();
    }

    std::string filename {argv[1]};

    if (solve(filename)) {
        return 0;
    } else {
        return 130;
    }
}
