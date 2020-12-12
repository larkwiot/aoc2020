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

    static std::unordered_set<std::string> eye_colors {
        "amb",
        "blu",
        "brn",
        "gry",
        "grn",
        "hzl",
        "oth",
    };

    int fields = 0;

    for (auto f : required_fields) {
        if (pass.contains(f)) {
            //std::cout << f << " ... yes\n";
            fields++;
        }
    }
    //std::cout << "has " << fields  << "/" << required_fields.size() << " fields\n";
    
    if (fields != required_fields.size()) {
        return false;
    }

    // year checks
    int byr = std::stoi(pass.at("byr"));
    if (byr > 2002 || byr < 1920) {
        std::cerr << "invalid byr: " << byr << "\n";
        return false;
    }
    int iyr = std::stoi(pass.at("iyr"));
    if (iyr > 2020 || iyr < 2010) {
        std::cerr << "invalid iyr: " << iyr << "\n";
        return false;
    }
    int eyr = std::stoi(pass.at("eyr"));
    if (eyr > 2030 || eyr < 2020) {
        std::cerr << "invalid eyr: " << eyr << "\n";
        return false;
    }

    reflex::BoostPerlMatcher hgtmatcher("^(\\d+)([a-z]{2})$", pass.at("hgt"));
    if (hgtmatcher.find() == 0) {
        std::cerr << "invalid height string: " << pass.at("hgt") << "\n";
        return false;
    }

    int hgt = std::stoi(std::string{hgtmatcher[1].first, hgtmatcher[1].second});
    std::string unit {hgtmatcher[2].first, hgtmatcher[2].second};
    if (unit != "cm" && unit != "in") {
        std::cerr << "[!] error: height unit was " << unit << "\n";
        //std::cerr << "\tline: " << pass.at("hgt") << "\n\theight: " << hgt << "\n";
        abort();
    } else if (unit == "cm" && (hgt < 150 || hgt > 193)) {
        std::cerr << "invalid hgt: " << hgt << "\n";
        return false;
    } else if (unit == "in" && (hgt < 59 || hgt > 76)) {
        std::cerr << "invalid hgt: " << hgt << "\n";
        return false;
    }

    if (!eye_colors.contains(pass.at("ecl"))) {
        std::cerr << "invalid ecl: " << pass.at("ecl") << "\n";
        return false;
    }

    reflex::BoostPerlMatcher pid_matcher("^\\d{9}$", pass.at("pid"));
    if (pid_matcher.find() == 0) {
        std::cerr << "invalid pid: " << pass.at("pid") << "\n";
        return false;
    }

    reflex::BoostPerlMatcher hair_matcher("^#[a-f0-9]{6}$", pass.at("hcl"));
    if (hair_matcher.find() == 0) {
        std::cerr << "invalid hcl: " << pass.at("hcl") << "\n";
        return false;
    }

    return true;
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
    if (new_line != "") {
        new_lines.emplace_back(new_line);
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