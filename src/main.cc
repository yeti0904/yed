#include "_components.hh"
#include "editor.hh"

int main(int argc, char** argv) {
    Editor editor;

    editor.HandleArguments(argc, argv);
    editor.Init();

    while (editor.run) {
        std::string input;
        fputs(editor.prompt.c_str(), stdout);
        fflush(stdout);
        std::getline(std::cin, input, '\n');

        editor.Run(input);
    }

    return 0;
}
