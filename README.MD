треба допомога
Please help!



TODO:

LEXER
-	read quotes and normal text, check them(DONE(for real this time))
-	read pipes and redirs(DONE)
-	protect memory(DONE)
-	(??)

PARSER
EXPANDER
EXECUTOR



MISC:
SIGNALS
BUILTINS
ADD HISTORY(backlog)

The shell reads its input from a file, from a string or from the user's terminal.

Input is broken up into words and operators, obeying the quoting rules, see Chapter 3. These tokens are separated by metacharacters. Alias expansion is performed.

The shell parses (analyzes and substitutes) the tokens into simple and compound commands.

Bash performs various shell expansions, breaking the expanded tokens into lists of filenames and commands and arguments.

Redirection is performed if necessary, redirection operators and their operands are removed from the argument list.

Commands are executed.

Optionally the shell waits for the command to complete and collects its exit status.
https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_04.html
