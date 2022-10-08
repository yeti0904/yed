# yed
a simple text editor i made for fun

## how to use
to edit 1 line, do `(line number) (text)`

for any other operations, use a command

## config
config is done using init.yed, either in %appdata%/yed or ~/.config/yed

it just contains yed commands

## running shell commands
type `$[shell input]` and it will execute shell input#

## commands
- `exit` (`x`)

exits the program

- `list {start} {end}` (`l`)

shows lines starting from {start} and ending at {end}

if these parameters are not given then it will display the entire file

- `linedistance [distance]` (`ld`)

sets the distance between line numbers when opening files

- `save {file name}` (`s`)

saves the file buffer into a file

if file name is not given then it will save the contents to the last opened/saved file

- `open [file name]` (`o`)

loads the contents of a file into the file buffer

- `search [string]` (`sr`)

searches the file buffer for given string and shows you what line the results are on

- `copy [source] [destination]` (`c`)

copies the contents of line source to line destination

- `alias [alias] [command]` (`a`)

creates an alias of command, so you can type the alias and it will execute command

- `size` (`sz`)

prints out the size of the file in bytes

- `clear` (`cl`)

deletes all lines in the file buffer

- `realline` (`rl`)

gets the real line number of a line in the file buffer, example:

```
10 hi
20 how are you
rl 20
2
ok
```

- `move [old] [new]` (`mv`)

moves line old into line new and then deletes line old

- `prompt [prompt]`

sets the prompt to prompt

- `renumber` (`rn`)

re-orders all lines so line numbers have an equal distance

- `ok {true/false}`

toggles printing "ok" after a command runs successfully