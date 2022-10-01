#include "_components.hh"
#include "fs.hh"
#include "util.hh"

int main() {
    size_t                      lineDistance = 10;
    std::map <int, std::string> buffer;
    std::string                 lastFileName;

    while (true) {
        std::string input;
        std::getline(std::cin, input, '\n');

        auto splitted = Util::SplitString(input, ' ');
        if (splitted.empty()) {
            continue;
        }

        if (Util::IsInteger(splitted[0])) {
            auto args = Util::SplitString(input, ' ', 2);
            if (args.empty()) {
                buffer[std::stol(splitted[0])] = "";
                continue;
            }

            buffer[std::stol(splitted[0])] = args[1];
        }
        else if (Util::LowerString(splitted[0]) == "exit") {
            puts("ok");
            return 0;
        }
        else if (Util::LowerString(splitted[0]) == "list") {
            std::vector <int> keys;
            for (auto [key, val] : buffer) {
                (void) val;
                keys.push_back(key);
            }

            if (splitted.size() < 3) {
                for (auto& key : keys) {
                    printf("  %i: %s\n", key, buffer[key].c_str());
                }
            }
            else {
                if (
                    !Util::IsInteger(splitted[1]) || !Util::IsInteger(splitted[2])
                ) {
                    fprintf(stderr, "parameters must be integers");
                    continue;
                }
            
                int begin = std::stoi(splitted[1]);
                int end   = std::stoi(splitted[2]);

                for (auto& key : keys) {
                    if ((key >= begin) && (key <= end)) {
                        printf("  %i: %s\n", key, buffer[key].c_str());
                    }
                }
            }
            puts("ok");
        }
        else if (Util::LowerString(splitted[0]) == "linedistance") {
            if (splitted.size() < 2) {
                fprintf(stderr, "1 parameter required\n");
                continue;
            }
            if (!Util::IsInteger(splitted[1])) {
                fprintf(stderr, "parameter must be an integer\n");
                continue;
            }
            lineDistance = std::stol(splitted[1]);
            puts("ok");
        }
        else if (Util::LowerString(splitted[0]) == "save") {
            if ((splitted.size() < 2) && lastFileName.empty()) {
                fprintf(stderr, "1 parameter required\n");
                continue;
            }
            std::string fileName;
            
            if (splitted.size() < 2) {
                printf("Save to %s? [Y/N] ", lastFileName.c_str());
                if (tolower(getchar()) != 'y') {
                    puts("abort");
                    continue;
                }
                fileName = lastFileName;
            }
            else {
                fileName     = splitted[1];
                lastFileName = fileName;
            }
            
            std::string fileContents;
            for (auto const& [key, val] : buffer) {
                (void) key;
                fileContents += val + '\n';
            }
            fileContents.erase(fileContents.length() - 1);

            FS::File::Write(fileName, fileContents);
            puts("ok");
        }
        else if (Util::LowerString(splitted[0]) == "open") {
            if (splitted.size() < 2) {
                fprintf(stderr, "1 parameter required\n");
                continue;
            }
            lastFileName = splitted[1];
            
            auto   lines = FS::File::ReadIntoVector(splitted[1]);
            size_t key   = lineDistance;
            buffer.clear();
            for (auto& line : lines) {
                buffer[key] = line;
            
                key += lineDistance;
            }
            puts("ok");
        }
        else if (Util::LowerString(splitted[0]) == "search") {
            if (splitted.size() < 2) {
                fprintf(stderr, "1 parameter required\n");
                continue;
            }
            for (auto const& [key, val] : buffer) {
                if (val.find(splitted[1]) != std::string::npos) {
                    printf("  %i: %s\n", key, val.c_str());
                }
            }
            puts("ok");
        }
        else if (Util::LowerString(splitted[0]) == "copy") {
            if (splitted.size() < 3) {
                fprintf(stderr, "2 parameters required\n");
                continue;
            }
            if (!Util::IsInteger(splitted[1]) || !Util::IsInteger(splitted[2])) {
                fprintf(stderr, "parameters must be integers\n");
                continue;
            }
            buffer[std::stoi(splitted[2])] = buffer[std::stoi(splitted[1])];
            puts("ok");
        }
        else {
            fprintf(stderr, "unrecognised command: %s\n", splitted[0].c_str());
        }
    }
}