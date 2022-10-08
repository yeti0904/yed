#ifndef YED_CONSTANTS_HH
#define YED_CONSTANTS_HH

#define APP_NAME    "yed"
#define APP_AUTHOR  "yeti0904"
#define APP_VERSION "1.2.0"

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
    "    copy [source] [destination] : copies the contents of line source to line destination\n" \
    "    alias [alias] [command] : creates an alias of command, so you can type the alias and it will execute command\n" \
    "    size : prints out the size of the file in bytes\n" \
    "    clear : deletes all lines in the file buffer\n" \
    "    realline : gets the real line number of a line in the file buffer\n" \
    "    move [old] [new] : moves line [old] into line [new] and then deletes line [old]\n" \
    "    prompt [prompt] : sets the prompt to [prompt]\n" \
    "    renumber : re-orders all lines so line numbers have an equal distance\n"

#endif