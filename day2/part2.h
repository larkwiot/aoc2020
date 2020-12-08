#include "../lib/util.h"

bool solve(std::string fn) {
    static reflex::Pattern policy("^(\\d)-(\\d) ([a-z]): ([a-z]+)$", "r");
    auto lines = read_file_lines(fn);
    int good_passwords = 0;

    for (auto l : lines) {
        reflex::StdMatcher matcher("^(\\d+)-(\\d+) ([a-z]): ([a-z]+)$", l);
        if(matcher.matches() != 0) {
            int lhs = stoi(std::string{matcher[1].first, matcher[1].second}) - 1;
            int rhs = stoi(std::string(matcher[2].first, matcher[2].second)) - 1;
            char letter = std::string(matcher[3].first, matcher[3].second)[0];
            std::string password {matcher[4].first, matcher[4].second};

            if (password[lhs] != password[rhs] &&
                (password[lhs] == letter || password[rhs] == letter)) {
                //std::cout << lhs << " " << rhs << " " << letter << " " << password.size() << "\n";
                //std::cout << l << " is valid\n";
                good_passwords++;
            }
        } else {
            std::cerr << "[!] error: policy regex did not match line:\n"
                      << l << "\n";
            abort();
        }
    }

    std::cout << "[-] finish: found #" << good_passwords << " good passwords\n";

    return true;
}
