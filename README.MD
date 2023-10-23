треба допомога
Please help!



TODO:

LEXER(DONE?)
-	read quotes and normal text, check them(DONE(for real this time))
-	read pipes and redirs(DONE)
-	protect memory(DONE)
-	check pipes and redirs(DONE)
-   changing exit code to 2 if syntax is wrong(DONE)
EXPANDER (postponed)
- change $stuff in WORD and DQUOTE types to their values, need to get enviroment + additional enviroment
PARSER(WIP)
- init command tables(WIP)
- put cmd and args in variables(WIP)
- figure out redirs and put the last ones in struct
- open them if needed (> lol > kek > pop)
- 

EXECUTOR



MISC:

SIGNALS

BUILTINS

ADD HISTORY(DONE)

The shell reads its input from a file, from a string or from the user's terminal.

Input is broken up into words and operators, obeying the quoting rules, see Chapter 3. These tokens are separated by metacharacters. Alias expansion is performed.

The shell parses (analyzes and substitutes) the tokens into simple and compound commands.

Bash performs various shell expansions, breaking the expanded tokens into lists of filenames and commands and arguments.

Redirection is performed if necessary, redirection operators and their operands are removed from the argument list.

Commands are executed.

Optionally the shell waits for the command to complete and collects its exit status.
https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_04.html
