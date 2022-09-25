#ifndef YED_UTIL_HH
#define YED_UTIL_HH

#include "_components.hh"

namespace Util {
    bool IsInteger(std::string str);
    std::vector <std::string> SplitString(
        std::string str, char splitter, ssize_t maxSplit = -1
    );
    std::string LowerString(std::string str);
}

#endif