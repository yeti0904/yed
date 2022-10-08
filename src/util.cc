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

std::string Util::GetConfigPath() {
	char* ret;
	#ifdef PLATFORM_WINDOWS
		ret = getenv("APPDATA");
		if (ret == nullptr) {
			ret = getenv("programfiles");
			if (ret == nullptr) {
				return ".";
			}
			return ret;
		}
		return ret;
	#else
		ret = getenv("HOME");
		if (ret == nullptr) {
			return ".";
		}
		return std::string(ret) + "/.config";
	#endif
}

std::string Util::CorrectPath(std::string path) {
	std::string ret;
	
	for (auto& ch : path) {
		#ifdef PLATFORM_WINDOWS
			if (ch == '/') {
				ret += '\\';
				continue;
			}
		#endif
		if (ret.empty()) {
			ret += ch;
			continue;
		}
		if ((ret.back() == '/') && (ch == '/')) {
			continue;
		}
		if ((ret.empty() || (ret.back() == '\\')) && (ch == '/')) {
			continue;
		}
		ret += ch;
	}

	return ret;
}

bool Util::IsBool(std::string str) {
	return (
		(str == "true") ||
		(str == "false")
	);
}

bool Util::ToBool(std::string str) {
	return str == "true";
}