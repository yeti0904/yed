#ifndef YED_EDITOR_HH
#define YED_EDITOR_HH

#include "_components.hh"
#include "fs.hh"
#include "util.hh"

class Editor {
	public:
		    bool                                               run;
		    size_t                                             lineDistance;
		    std::map <int, std::string>                        buffer;
		    std::string                                        lastFileName;
		    std::vector <std::pair <std::string, std::string>> aliases;
		    std::string                                        prompt;
		    bool                                               showOk;
		    int                                                tabSize;

		    Editor();
		    ~Editor();
		    void HandleArguments(int argc, char** argv);
		    void CreateConfigFiles();
		    void Init();
		    void Run(std::string input);
		    void Ok();
};

#endif