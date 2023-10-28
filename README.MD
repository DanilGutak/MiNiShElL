треба допомога
Please help!



# TODO:

- some tests(VITALIK)

- write descriptions for functions(DONE)
- replace all printf to putstr_fd 


## CLEANER(??) after every rdln
- clean tokens(DONE)
- clean cmdtable(DONE)
- prepare path(?)
- ??

## LEXER(DONE?)
-	read quotes and normal text, check them(DONE(for real this time))
-	read pipes and redirs(DONE) (redo the redir check logic) (REDO PUTSYNTAX ERROR) (DONE)
-	protect memory(DONE)
-	check pipes and redirs(DONE)
-   changing exit code to 2 if syntax is wrong(DONE)

## EXPANDER (postponed) (VITALIK?)
- change $stuff in WORD and DQUOTE types to their values, need to get enviroment + additional enviroment

## PARSER(DONE)
- init command tables(DONE)
- put args together fo no_space == 1 (DONE)
- put cmd and args in variables(DONE)
- figure out redirs and them in struct(DONE)


 ## EXECUTOR
- open redirs (> lol > kek > pop)(VITALIK)
- trigger heredocs if anywhere (do expands(dont forget about "eof" does not expand))(VITALIK)
- set the fd for redir(last for in and last for out[not heredoc])(VITALIK?)
- execute different part of pipes one after another(WIP)
- find executable for builtins(now cannot find it) (WIP)
- configure pipe for it(WIP)
- check exit codes of execve and set it accordingly



## MISC:

- signals

- builts

    ◦ echo with option -n

    ◦ cd with only a relative or absolute path

    ◦ pwd with no options

    ◦ export with no options

    ◦ unset with no options

    ◦ env with no options or arguments

    ◦ exit with no options (DONE, need to change output to stderror)

- add history (DONE)



## NOTES
- bash is stupid
## finding executable
- searches from left to right in path variables
- if finds check whether executable if not go further until the end. 
- BUT if noone is executable return 1st is run and permision denied is returned

The shell reads its input from a file, from a string or from the user's terminal.

Input is broken up into words and operators, obeying the quoting rules, see Chapter 3. These tokens are separated by metacharacters. Alias expansion is performed.

The shell parses (analyzes and substitutes) the tokens into simple and compound commands.

Bash performs various shell expansions, breaking the expanded tokens into lists of filenames and commands and arguments.

Redirection is performed if necessary, redirection operators and their operands are removed from the argument list.

Commands are executed.

Optionally the shell waits for the command to complete and collects its exit status.
## Useful links

https://www.maizure.org/projects/decoded-gnu-coreutils/

https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_04.html

https://www.gnu.org/software/bash/manual/bash.html#Command-Search-and-Execution

