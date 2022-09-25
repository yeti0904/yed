#include "util.hh"

bool Util::IsInteger(std::string str) {
    for (auto& ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

std::vector <std::string> Util::SplitString(
    std::string str, char splitter, ssize_t maxSplit
) {
    ssize_t                   splits = 0;
    std::string               reading;
    std::vector <std::string> ret;
    
    for (size_t i = 0; i <= str.length(); ++i) {
        if ((str[i] == splitter) || (str[i] == '\0')) {
            if ((maxSplit < 0) || (splits < maxSplit - 1) || (str[i] == '\0')) {
                if (reading == "") {
                    continue;
                }
                ret.push_back(reading);
                reading = "";
                ++ splits;
                continue;
            }
            reading += splitter;
            continue;
        }
        reading += str[i];
    }

    return ret;
}

std::string Util::LowerString(std::string str) {
    std::string ret;
    for (auto& ch : str) {
        ret += tolower(ch);
    }
    return ret;
}