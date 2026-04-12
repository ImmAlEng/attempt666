* Check there are no malicious aliases or misleading helper scripts.
* If you have not finished minishell yourself, read the full subject before evaluating.
* Any segfault or unexpected termination during the defense means grade 0.
* Check for memory leaks with tools like `valgrind`, `leaks`, or `e_fence`. 

**Mandatory part**
<!-- 
* README.md Compliance Check

  * `README.md` exists at repo root.
  * First line is exactly italicized in the required 42 format.
  * Has a **Description** section.
  * Has an **Instructions** section.
  * Has a **Resources** section, including how AI was used.
  * If any required element is missing, the grade is 0.  -->
* Compile

  * Use `make -n`.
  * Check for `-Wall -Wextra -Werror`.
  * Project compiles without errors.
  * Makefile must not relink.
* Simple Command & global variables

  * Run a simple command with absolute path like `/bin/ls`.
  * Ask how many globals are used and why.
  * Global variable may only store received signal number.
  * Test empty command.
  * Test commands with only spaces or tabs.
* Arguments

  * Run commands with arguments, no quotes.
  * Repeat with different commands and args.
* echo

  * Test `echo` with and without args.
  * Test `-n`.
* exit

  * Test `exit` with and without args.
  * Relaunch minishell after exit tests.
* Return value of a process

  * Run a command, then `echo $?`.
  * Compare with bash.
  * Repeat with valid and invalid commands.
  * Try expressions like `expr $? + $?`.
* Signals

  * `Ctrl-C` on empty prompt → new line + fresh prompt.
  * `Ctrl-\` on empty prompt → nothing.
  * `Ctrl-D` on empty prompt → exits minishell.
  * `Ctrl-C` after typing text → new line + fresh prompt.
  * Press Enter after that; old buffer must be cleared.
  * `Ctrl-D` after typing text → nothing.
  * `Ctrl-\` after typing text → nothing.
  * Test `Ctrl-C`, `Ctrl-\`, `Ctrl-D` with blocking commands like `cat` or `grep`.
* Double Quotes

  * Test commands with double quotes and spaces inside quotes.
  * Try `echo "cat lol.c | cat > lol.c"`.
  * Try anything except `$`.
* Single Quotes

  * Test single-quoted arguments.
  * Test empty args.
  * Test env vars, spaces, pipes, redirections inside single quotes.
  * `echo '$USER'` must print `$USER`.
  * Nothing inside single quotes should be interpreted.
* env

  * `env` shows current environment variables.
* export

  * Create and replace environment variables.
  * Check results with `env`.
* unset

  * Remove variables with `unset`.
  * Check results with `env`.
* cd

  * Change working directory and verify with `/bin/ls`.
  * Repeat with valid and invalid `cd`.
  * Test `.` and `..`.
* pwd

  * Test `pwd` in different directories.
* Relative Path

  * Execute commands using relative paths.
  * Repeat in different directories with complex relative paths.
* Environment path

  * Run commands without explicit path: `ls`, `wc`, `awk`, etc.
  * Unset `$PATH` and confirm commands stop working.
  * Set `$PATH` to multiple directories and verify left-to-right lookup order.
* Redirection

  * Test `<`, `>`, `>>`.
  * Repeat with different commands and args.
  * Check repeated same redirections.
  * Test `<<` heredoc.
* Pipes

  * Test pipelines like `cat file | grep bla | more`.
  * Repeat with different commands.
  * Try invalid commands in pipeline.
  * Mix pipes and redirections.
* Go Crazy and history

  * Type a command, press `Ctrl-C`, then Enter; buffer must be empty.
  * Check Up/Down history navigation.
  * Retry old commands.
  * Run invalid commands like `dsbksdgbksdghsd`; should error, not crash.
  * `cat | cat | ls` should behave normally.
  * Try very long commands with many args.
* Environment variables

  * Test `echo $VARIABLE`.
  * Confirm `$` expansion works.
  * Confirm double quotes still interpolate `$`.
  * Ensure `USER` exists, otherwise set it.
  * `echo "$USER"` should print its value.

