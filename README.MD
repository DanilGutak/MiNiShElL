треба допомога
Please help!



TODO:

SOME TESTS(VITALIK)

-write descriptions for functions(backlog)


CLEANER(??) after every rdln
-clean tokens(DONE)
-clean cmdtable(DONE)
-prepare path?
- ??

LEXER(DONE?)
-	read quotes and normal text, check them(DONE(for real this time))
-	read pipes and redirs(DONE)
-	protect memory(DONE)
-	check pipes and redirs(DONE)
-   changing exit code to 2 if syntax is wrong(DONE)

EXPANDER (postponed)
- change $stuff in WORD and DQUOTE types to their values, need to get enviroment + additional enviroment(VITALIK?)

PARSER(WIP)
- init command tables(DONE)
- put args together fo no_space == 1 (DONE)
- put cmd and args in variables(DONE)
- figure out redirs and them in struct, prob 2 arrays of tokens (<<&<, >&>>)(backlog)
- open them if needed (> lol > kek > pop)(VITALIK)(in exec prob?)

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
