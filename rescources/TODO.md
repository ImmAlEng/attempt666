# 🧠 Minishell TODO

A structured list of tasks and progress tracking for the Minishell project (42 standard).

---

## ⚙️ BUILTINS

### Implement
- [x] `echo` — with `-n` option
- [x] `cd` — with relative, absolute, and `~` paths
- [x] `pwd` — prints current working directory
- [x] `export` — add or modify environment variables
- [x] `unset` — remove variables from environment
- [x] `env` — display the environment
- [x] `exit` — exit the shell with correct code

### Notes
- Builtins must work both standalone and inside pipelines.
- Environment changes (`export`, `unset`) affect only the current shell.
- `cd` must update `PWD` and `OLDPWD`.
- `exit` must respect numeric argument behavior (`exit 2`, etc.).

---

## 🧩 PARSING

### Tokenization
- [x] Split input into tokens separated by spaces and special characters.
- [x] Handle quotes: single (`'`) and double (`"`).
- [x] Handle redirections (`<`, `>`, `>>`, `<<`).
- [x] Remove quotes from final arguments.
- [x] Handle `$` variable expansion inside double quotes and unquoted text.
- [x] No globbing (`*`, `?`, etc.) or backslash escaping required.

### Syntax Validation
- [x] Detect unclosed quotes.
- [x] Detect misplaced pipes or redirections (`|`, `>`, `<`).
- [x] Ensure correct syntax for heredocs (`<<`).

### Command Structure
- [x] Build a simple structure or list representing commands and arguments.
- [x] Identify redirections and pipes for each command node.

---

## 🚨 ERROR HANDLING

### Parser Errors
- [x] Detect and report syntax errors (e.g. unclosed quotes, invalid tokens).
- [x] Return exit code `258` for syntax errors.

### Execution Errors
- [x] Handle "command not found".
- [x] Handle permission denied and execution errors.
- [x] Handle invalid file redirections.
- [x] Handle failed `fork` or `pipe` calls gracefully.
- [x] Properly close file descriptors on all errors.

---

## 🔗 PIPELINES & REDIRECTIONS

- [x] Implement multiple pipes (e.g. `cmd1 | cmd2 | cmd3`).
- [x] Implement input/output redirections: `<`, `>`, `>>`, `<<`.
- [x] Handle heredocs (with variable expansion inside).
- [x] Combine pipes and redirections correctly.
- [x] Close unused file descriptors.
- [x] Wait for all child processes before returning to prompt.

---

## 🌱 ENVIRONMENT MANAGEMENT

- [x] Duplicate environment variables on startup.
- [x] Implement `$VAR` and `$?` expansion.
- [x] Update environment dynamically (`export`, `unset`).
- [x] Handle `$` inside double quotes correctly.
- [x] Builtins should operate on internal environment structure.

---

## 🧠 SIGNALS

- [x] Handle `SIGINT` (Ctrl+C) — interrupt current input, display new prompt.
- [x] Handle `SIGQUIT` (Ctrl+\) — ignored in parent, displayed in child.
- [x] Handle `EOF` (Ctrl+D) — exit gracefully if line is empty.
- [x] Restore default signal behavior for child processes.
- [x] Suppress unwanted `^C` and `Quit (core dumped)` messages.

---

## 🧪 TESTSUITE

- [x] Create test scripts for builtins.
- [x] Create tests for syntax errors.
- [x] Create tests for redirections and pipes.
- [x] Create tests for variable expansion.
- [x] Compare minishell output and exit codes with bash.
- [x] Integrate with `run_tests.sh` for automated checks.

---

## 🔧 GENERAL

- [x] Ensure no memory leaks (use `valgrind` or `leaks`).
- [x] Handle all system call errors properly.
- [x] Maintain code readability and consistent style.
- [x] Free all allocated memory before exit.
- [ ] Follow 42 Norm standards.

---

### 📦 FUTURE IDEAS (optional)


