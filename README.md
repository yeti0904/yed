# yed
a simple text editor i made for fun

## how to use
to edit 1 line, do `(line number) (text)`

for any other operations, use a command

## commands
- `exit`

exits the program

- `list {start} {end}`

shows lines starting from {start} and ending at {end}

if these parameters are not given then it will display the entire file

- `linedistance [distance]`

sets the distance between line numbers when opening files

- `save {file name}`

saves the file buffer into a file

if file name is not given then it will save the contents to the last opened/saved file

- `open [file name]`

loads the contents of a file into the file buffer

- `search [string]`

searches the file buffer for given string and shows you what line the results are on

- `copy [source] [destination]`

copies the contents of line source to line destination