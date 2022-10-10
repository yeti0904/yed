#include "editor.hh"
#include "constants.hh"

Editor::Editor():
	run(true),
	lineDistance(10),
	showOk(false),
	tabSize(4)
{
	aliases = {
    	std::make_pair("x",  "exit"),
    	std::make_pair("l",  "list"),
    	std::make_pair("ld", "linedistance"),
    	std::make_pair("s",  "save"),
    	std::make_pair("o",  "open"),
    	std::make_pair("sr", "search"),
    	std::make_pair("c",  "copy"),
    	std::make_pair("a",  "alias"),
    	std::make_pair("sz", "size"),
    	std::make_pair("cl", "clear"),
    	std::make_pair("rl", "realline"),
    	std::make_pair("mv", "move"),
    	std::make_pair("pr", "prompt"),
    	std::make_pair("rn", "renumber"),
    	std::make_pair("ts", "tabSize")
	};
}

Editor::~Editor() {
	
}

void Editor::HandleArguments(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            std::string arg = argv[i];
            if ((arg == "--help") || (arg == "-h")) {
                printf("%s [file name] {parameters}\n%s\n", argv[0], APP_HELP);
                run = false;
                return;
            }
            else if ((arg == "--version") || (arg == "-v")) {
                printf("%s %s\nmade by %s\n", APP_NAME, APP_VERSION, APP_AUTHOR);
                run = false;
                return;
            }
            else {
                fprintf(stderr, "unrecognised argument: %s\n", argv[i]);
                exit(1);
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
            lastFileName = argv[i];
            printf("opened %s\n", argv[i]);
        }
    }
}

void Editor::Init() {
	// create files
	if (!FS::Directory::Exists(Util::CorrectPath(Util::GetConfigPath()))) {
		FS::Directory::Create(Util::CorrectPath(Util::GetConfigPath()));
	}
	
	std::string configPath = Util::CorrectPath(Util::GetConfigPath() + "/yed");

	if (!FS::Directory::Exists(configPath)) {
		FS::Directory::Create(configPath);
	}
	
	std::string init = Util::CorrectPath(Util::GetConfigPath() + "/yed/init.yed");
	if (!FS::File::Exists(init)) {
		FS::File::Write(init, "");
	}

	// run init script
	for (auto& line : FS::File::ReadIntoVector(init)) {
		Run(line);
	}
	showOk = true;
}

void Editor::Run(std::string input) {
	if (input[0] == '$') {
		system(input.substr(1).c_str());
		return;
	}

	auto splitted = Util::SplitString(input, ' ');
	if (splitted.empty()) {
	    return;
	}

	for (auto& pair : aliases) {
		if (splitted[0] == pair.first) {
			splitted[0] = pair.second;
			break;
		}
	}

	if (Util::IsInteger(splitted[0])) {
	    auto args = Util::SplitString(input, ' ', 2);
	    if (args.size() == 1) {
	        buffer.erase(std::stoi(splitted[0]));
	        return;
	    }

	    buffer[std::stol(splitted[0])] = args[1];
	}
	else if (Util::LowerString(splitted[0]) == "exit") {
	    Ok();
	    run = false;
	    return;
	}
	else if (Util::LowerString(splitted[0]) == "list") {
	    std::vector <int> keys;
	    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
	        keys.push_back(it->first);
	    }

	    if (splitted.size() < 3) {
	        for (auto& key : keys) {
            	printf("  %i: ", key);
            	for (auto& ch : buffer[key]) {
            		switch (ch) {
            			case '\t': {
            				for (int i = 0; i < tabSize; ++i) {
            					putchar(' ');
            				}
            			}
            			default: {
                			putchar(ch);
                		}
                	}
                }
                putchar('\n');
	        }
	    }
	    else {
	        if (
	            !Util::IsInteger(splitted[1]) || !Util::IsInteger(splitted[2])
	        ) {
	            fprintf(stderr, "parameters must be integers");
	            return;
	        }
	    
	        int begin = std::stoi(splitted[1]);
	        int end   = std::stoi(splitted[2]);

	        for (auto& key : keys) {
	            if ((key >= begin) && (key <= end)) {
	            	printf("  %i: ", key);
	            	for (auto& ch : buffer[key]) {
	            		switch (ch) {
	            			case '\t': {
	            				for (int i = 0; i < tabSize; ++i) {
	            					putchar(' ');
	            				}
	            			}
	            			default: {
	                			putchar(ch);
	                		}
	                	}
	                }
	                putchar('\n');
	            }
	        }
	    }
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "linedistance") {
	    if (splitted.size() < 2) {
	        fprintf(stderr, "1 parameter required\n");
	        return;
	    }
	    if (!Util::IsInteger(splitted[1])) {
	        fprintf(stderr, "parameter must be an integer\n");
	        return;
	    }
	    lineDistance = std::stol(splitted[1]);
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "save") {
	    if ((splitted.size() < 2) && lastFileName.empty()) {
	        fprintf(stderr, "1 parameter required\n");
	        return;
	    }
	    std::string fileName;
	    
	    if (splitted.size() < 2) {
	        printf("Save to %s? [Y/N] ", lastFileName.c_str());
	        fflush(stdout);
	        if (tolower(getchar()) != 'y') {
	            puts("abort");
	            return;
	        }
	        fileName = lastFileName;
	    }
	    else {
	        fileName     = splitted[1];
	        lastFileName = fileName;
	    }
	    
	    std::string fileContents;
	    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
	        fileContents += it->second + '\n';
	    }
	    fileContents.erase(fileContents.length() - 1);

	    FS::File::Write(fileName, fileContents);
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "open") {
	    if (splitted.size() < 2) {
	        fprintf(stderr, "1 parameter required\n");
	        return;
	    }
	    lastFileName = splitted[1];
	    
	    auto   lines = FS::File::ReadIntoVector(splitted[1]);
	    size_t key   = lineDistance;
	    buffer.clear();
	    for (auto& line : lines) {
	        buffer[key] = line;
	    
	        key += lineDistance;
	    }
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "search") {
	    if (splitted.size() < 2) {
	        fprintf(stderr, "1 parameter required\n");
	        return;
	    }
	    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
	        if (it->second.find(splitted[1]) != std::string::npos) {
	            printf("  %i: %s\n", it->first, it->second.c_str());
	        }
	    }
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "copy") {
	    if (splitted.size() < 3) {
	        fprintf(stderr, "2 parameters required\n");
	        return;
	    }
	    if (!Util::IsInteger(splitted[1]) || !Util::IsInteger(splitted[2])) {
	        fprintf(stderr, "parameters must be integers\n");
	        return;
	    }
	    buffer[std::stoi(splitted[2])] = buffer[std::stoi(splitted[1])];
	    Ok();
	}
	else if (Util::LowerString(splitted[0]) == "alias") {
		if (splitted.size() < 3) {
			fprintf(stderr, "2 parameters required\n");
			return;
		}

		aliases.push_back(std::make_pair(splitted[1], splitted[2]));
		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "movelines") {
		puts("unfinished command");
		return;
		if (splitted.size() < 4) {
			fprintf(stderr, "3 parameters required\n");
			return;
		}
		if (
			(!Util::IsInteger(splitted[1]) && (splitted[1] != "*")) ||
			(!Util::IsInteger(splitted[2]) && (splitted[2] != "*")) ||
			(!Util::IsInteger(splitted[3]))
		) {
			fprintf(stderr, "parameters must be integers\n");
			return;
		}

		int start, end;
		start = splitted[1] == "*"? 0 : std::stoi(splitted[1]);
		end   = splitted[2] == "*"? buffer.end()->first : std::stoi(splitted[2]);

		if (end < start) {
			fprintf(stderr, "end line must be after start line\n");
			return;
		}

		int moveBy = std::stoi(splitted[3]);

	    for (auto it = buffer.end(); it != buffer.begin(); --it) {
	        if ((it->first >= start) && (it->first <= end)) {
	        	buffer[it->first + moveBy] = it->second;
	        	buffer.erase(it->first);
	        }
	    }
	}
	else if (Util::LowerString(splitted[0]) == "size") {
		size_t size = 0;
		for (auto it = buffer.begin(); it != buffer.end(); ++it) {
			size += it->second.size();
		}
		printf("%llu\n", (long long int) size);
		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "clear") {
		buffer.clear();
		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "realline") {
		if (splitted.size() < 2) {
			fprintf(stderr, "1 parameter required\n");
			return;
		}
		if (!Util::IsInteger(splitted[1])) {
			fprintf(stderr, "parameter must be integer\n");
			return;
		}

		int line = std::stoi(splitted[1]);
		int i = 0;
		for (auto it = buffer.begin(); it != buffer.end(); ++it) {
			++ i;
			if (it->first == line) {
				printf("%i\n", i);
				Ok();
				return;
			}
		}

		if (buffer.count(line) == 0) {
			fprintf(stderr, "line %i doesn't exist\n", line);
		}
	}
	else if (Util::LowerString(splitted[0]) == "move") {
		if (splitted.size() < 3) {
			fprintf(stderr, "2 parameters required\n");
			return;
		}
		if (
			(!Util::IsInteger(splitted[1])) ||
			(!Util::IsInteger(splitted[2]))
		) {
			fprintf(stderr, "parameters must be integers");
			return;
		}

		int oldLine, newLine;
		oldLine = std::stoi(splitted[1]);
		newLine = std::stoi(splitted[2]);

		buffer[newLine] = buffer[oldLine];
		buffer.erase(oldLine);
		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "prompt") {
		if (splitted.size() < 2) {
			prompt = "";
		}
		else {
			prompt = splitted[1];
		}
		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "renumber") {
		std::vector <std::string> lines;
		
		for (auto it = buffer.begin(); it != buffer.end(); ++it) {
			lines.push_back(it->second);
		}
		
		buffer.clear();
		size_t lineNumber = 0;
		for (auto& line : lines) {
			lineNumber += lineDistance;
			buffer[lineNumber] = line;
		}

		Ok();
	}
	else if (Util::LowerString(splitted[0]) == "ok") {
		if (splitted.size() < 2) {
			showOk = !showOk;
			puts(showOk? "true" : "false");
		}
		else {
			if (Util::IsBool(splitted[1])) {
				showOk = Util::ToBool(splitted[1]);
				Ok();
			}
			else {
				fprintf(stderr, "parameters must be booleans");
			}
		}
	}
	else if (Util::LowerString(splitted[0]) == "tabsize") {
		if (splitted.size() < 2) {
			fprintf(stderr, "1 parameter required\n");
			return;
		}
		if (!Util::IsInteger(splitted[1])) {
			fprintf(stderr, "parameter must be integer\n");
			return;
		}
		tabSize = std::stoi(splitted[1]);
		Ok();
	}
	else {
	    fprintf(stderr, "unrecognised command: %s\n", splitted[0].c_str());
	}
}

void Editor::Ok() {
	if (showOk) {
		puts("ok");
	}
}