#include "_components.hh"
#include "fs.hh"
#include "util.hh"

#define APP_NAME    "yed"
#define APP_AUTHOR  "yeti0904"
#define APP_VERSION "1.0.0"

#define APP_HELP \
    "COMMAND PARAMETERS\n" \
    "    --help / -h : show this menu\n" \
    "    --version / -v : show app version\n" \
    "USING THE APP\n" \
    "line edit with: (line number) (text)\n" \
    "commands:\n" \
    "    exit : exit the app\n" \
    "    list {start} {end} : show lines starting from {start} and ending at {end}\n" \
    "                         if these parameters are not given then it will display the entire file\n" \
    "    linedistance [distance] : sets the distance between line numbers when opening files\n" \
    "    save {file name} : saves the file buffer into a file, if file name is not given then it will save the contents to the last opened/saved file\n" \
    "    open [file name] : loads the contents of a file into the file buffer\n" \
    "    search [string] : searches the file buffer for given string and shows you what line the results are on\n" \
    "    copy [source] [destination] : copies the contents of line source to line destination\n"

int main(int argc, char** argv) {
    size_t                      lineDistance = 10;
    std::map <int, std::string> buffer;
    std::string                 lastFileName;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            std::string arg = argv[i];
            if ((arg == "--help") || (arg == "-h")) {
                printf("%s [file name] {parameters}\n%s\n", argv[0], APP_HELP);
                return 0;
            }
            else if ((arg == "--version") || (arg == "-v")) {
                printf("%s %s\nmade by %s\n", APP_NAME, APP_VERSION, APP_AUTHOR);
                return 0;
            }
            else {
                fprintf(stderr, "unrecognised argument: %s\n", argv[i]);
                return 1;
            }
        }
        else {
            auto   lines = FS::File::ReadIntoVector(argv[1]);
            size_t key   = lineDistance;
            buffer.clear();
            for (auto& line : lines) {
                buffer[key] = line;
            
                key += lineDistance;
            }
            printf("opened %s\n", argv[i]);
        }
    }

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