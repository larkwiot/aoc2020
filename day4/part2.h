#include "../lib/util.h"

bool is_passport_valid(std::unordered_map<std::string, std::string> pass) {
    static std::unordered_set<std::string> required_fields {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid",
        //"cid",
    };

    int fields = 0;

    for (auto f : required_fields) {
        if (pass.contains(f)) {
            //std::cout << f << " ... yes\n";
            fields++;
        }
    }
    //std::cout << "has " << fields  << "/" << required_fields.size() << " fields\n";
    
    return fields == required_fields.size();
}

bool solve(std::string fn) {
    auto lines = read_file_lines(fn);
    std::vector<std::string> new_lines {};
    
    // pre-process the input, such that every passport
    // is now on one line
    std::string new_line;
    for (auto l : lines) {
        if (l != "") {
            new_line += " " + l;
        } else {
            new_lines.emplace_back(new_line);
            new_line = "";
        }
    }

    int valid_passports = 0;

    // now each line is a single passport we can parse
    for (auto l : new_lines) {
        //std::cout << l << "\n";
        std::unordered_map<std::string, std::string> fields {};
        reflex::BoostPerlMatcher matcher("([a-z]{3}):(\\S+)", l);
        while (matcher.find() != 0) {
            fields.emplace(
                std::string {matcher[1].first, matcher[1].second},
                std::string {matcher[2].first, matcher[2].second}
            );
        }

        if (is_passport_valid(fields)) {
            valid_passports++;
        }
    }

    std::cout << "[-] finish: found #" << valid_passports << " valid passports\n";

    return true;
}