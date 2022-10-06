#include "_components.hh"
#include "editor.hh"

int main(int argc, char** argv) {
	Editor editor;

	editor.HandleArguments(argc, argv);

    while (editor.run) {
        std::string input;
        std::getline(std::cin, input, '\n');

		editor.Run(input);
	}

	return 0;
}
