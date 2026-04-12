*This project has been created as part of the 42 curriculum by amkhuder, imengels.*

## Description

Minishell is a simplified version of bash that implements core shell functionality including
command execution, pipes, redirections, environment variable management, and built-in commands.
The project aims to provide a deeper understanding of process creation, file descriptors, system
calls, and how shells work under the hood.
Builtin functions are limited in their implementation (check subject).
Error codes are not identical to bash !!!

## Instructions

Compilation:

make

Execution:

./minishell
+ give normal bash commands.

## Resources

System Call Manual Pages
https://www.youtube.com/watch?v=FpljIU9Z-f8
https://www.youtube.com/watch?v=yTR00r8vBH8
https://www.rozmichelle.com/pipes-forks-dups/ - Understanding pipes, forks, and dups
https://github.com/itislu/42_minishell_tester/tree/master - Minishell tester by "itislu"


AI Usage:

AI (Claude by Anthropic) was used as a learning assistant during the development of this project for the following purposes:
- Process Management (forks, execve, etc...)
- File Descriptors (dup, redirs, pipes, etc...)
- Heredoc
- and further debugging assistance...

AI was not used for writing core implementation code !

---

*That's it, folks!*
