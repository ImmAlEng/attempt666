## Totals

- Different stderr pairs scanned: 401
- Semantic mismatches found: 149

## Valgrind messages (all together)

- Combined file: all_valgrind_messages.txt
- Valgrind files merged: 127
- Total combined lines: 24052

## FD smoke status (after fix)

- pipe2: gt4_fd_lines=0
- pipe3: gt4_fd_lines=0
- redir_pipe: gt4_fd_lines=0
- heredoc_simple: gt4_fd_lines=0
- heredoc_pipe2: gt4_fd_lines=0
- heredoc_pipe3: gt4_fd_lines=0
- multi_cmd: gt4_fd_lines=0

Notes:
- Each case was run with valgrind --track-fds=yes.
- No case produced "FILE DESCRIPTORS: N open" with N > 4.

## Category transitions

- 1 : ambiguous_redirect -> enoent
- 1 : enoent -> command_not_found
- 21 : other -> command_not_found
- 36 : invalid_identifier -> other
- 3 : command_not_found -> perm_denied
- 3 : is_directory -> perm_denied
- 84 : syntax_unexpected_token -> syntax_generic

## Highest-priority semantic mismatches

1. ambiguous redirect -> enoent
- 11_expansion/4_stderr_minishell | bash: $notexists: ambiguous redirect | mini: open: No such file or directory

2. command_not_found -> perm_denied
- 1_scmds/25_stderr_minishell | bash: .: command not found | mini: execve: Permission denied
- 8_syntax_errors/19_stderr_minishell | bash: .: command not found | mini: execve: Permission denied
- 8_syntax_errors/20_stderr_minishell | bash: ..: command not found | mini: execve: Permission denied

3. is_directory -> perm_denied
- 1_scmds/36_stderr_minishell | bash: /bin/: Is a directory | mini: execve: Permission denied
- 8_syntax_errors/12_stderr_minishell | bash: /home/immanuel: Is a directory | mini: execve: Permission denied
- 8_syntax_errors/37_stderr_minishell | bash: /: Is a directory | mini: execve: Permission denied

4. enoent -> command_not_found
<!-- - 2_path_check/14_stderr_minishell | bash: ls: No such file or directory | mini: command not found -->

## Likely semantic but lower confidence

<!-- - syntax_unexpected_token -> syntax_generic (loss of unexpected token detail):
  - 10_parsing_hell/122_stderr_minishell | bash: syntax error near unexpected token `|' | mini: syntax error
  - 1_pipelines/33_stderr_minishell | bash: syntax error near unexpected token `|' | mini: syntax error
  - 1_scmds/40_stderr_minishell | bash: syntax error near unexpected token `|' | mini: syntax error
  - 1_scmds/41_stderr_minishell | bash: syntax error near unexpected token `|' | mini: syntax error
  - 8_syntax_errors/10_stderr_minishell | bash: syntax error near unexpected token `<' | mini: syntax error
  - 8_syntax_errors/11_stderr_minishell | bash: syntax error near unexpected token `<<' | mini: syntax error
  - 8_syntax_errors/13_stderr_minishell | bash: syntax error near unexpected token `<' | mini: syntax error
  - 8_syntax_errors/14_stderr_minishell | bash: syntax error near unexpected token `<' | mini: syntax error
  - 8_syntax_errors/15_stderr_minishell | bash: syntax error near unexpected token `newline' | mini: syntax error
  - 8_syntax_errors/17_stderr_minishell | bash: syntax error near unexpected token `newline' | mini: syntax error
  - 8_syntax_errors/18_stderr_minishell | bash: syntax error near unexpected token `<' | mini: syntax error
  - 8_syntax_errors/1_stderr_minishell | bash: syntax error near unexpected token `newline' | mini: syntax error
  - 8_syntax_errors/21_stderr_minishell | bash: syntax error near unexpected token `|' | mini: syntax error
  - 8_syntax_errors/24_stderr_minishell | bash: syntax error near unexpected token `newline' | mini: syntax error
  - 8_syntax_errors/25_stderr_minishell | bash: syntax error near unexpected token `newline' | mini: syntax error -->
<!-- - invalid_identifier -> other (message class changed to generic):
  - 1_builtins_export/14_stderr_minishell | bash: export: `0': not a valid identifier | mini: arg not valid
  - 1_builtins_export/19_stderr_minishell | bash: export: `=': not a valid identifier | mini: arg not valid
  - 1_builtins_export/20_stderr_minishell | bash: export: `===': not a valid identifier | mini: arg not valid
  - 1_builtins_export/21_stderr_minishell | bash: export: `===': not a valid identifier | mini: arg not valid
  - 1_builtins_export/22_stderr_minishell | bash: export: `TE-ST=100': not a valid identifier | mini: arg not valid
  - 1_builtins_export/23_stderr_minishell | bash: export: `TEST-=100': not a valid identifier | mini: arg not valid
  - 1_builtins_export/25_stderr_minishell | bash: export: `==========': not a valid identifier | mini: arg not valid
  - 1_builtins_export/26_stderr_minishell | bash: export: `1TEST=': not a valid identifier | mini: arg not valid
  - 1_builtins_export/27_stderr_minishell | bash: export: `=': not a valid identifier | mini: arg not valid
  - 1_builtins_export/29_stderr_minishell | bash: export: `TE+S=T=': not a valid identifier | mini: arg not valid
  - 1_builtins_export/30_stderr_minishell | bash: export: `TES.T=123': not a valid identifier | mini: arg not valid
  - 1_builtins_export/31_stderr_minishell | bash: export: `TES.T=123': not a valid identifier | mini: arg not valid
  - 1_builtins_export/32_stderr_minishell | bash: export: `TES+T=123': not a valid identifier | mini: arg not valid
  - 1_builtins_export/34_stderr_minishell | bash: export: `TES}T=123': not a valid identifier | mini: arg not valid
  - 1_builtins_export/35_stderr_minishell | bash: export: `TES{T=123': not a valid identifier | mini: arg not valid -->
- other -> command_not_found (bash often emits nothing or a different warning):
  - 10_parsing_hell/12_stderr_minishell | bash:  | mini: command not found
  - 10_parsing_hell/14_stderr_minishell | bash:  | mini: command not found
  - 10_parsing_hell/15_stderr_minishell | bash:  | mini: command not found
  - 1_pipelines/25_stderr_minishell | bash:  | mini: command not found
  - 1_pipelines/26_stderr_minishell | bash:  | mini: command not found
  - 1_pipelines/27_stderr_minishell | bash:  | mini: command not found
  - 1_pipelines/28_stderr_minishell | bash:  | mini: command not found
  - 1_pipelines/29_stderr_minishell | bash: warning: here-document at line 11 delimited by end-of-file (wanted `stop3') | mini: command not found
  - 1_pipelines/30_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/80_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/81_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/82_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/83_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/84_stderr_minishell | bash:  | mini: command not found
  - 1_redirs/85_stderr_minishell | bash:  | mini: command not found

## Full list (all semantic mismatches)

Format: path | bash_category -> mini_category | bash_first_nonempty_stderr | mini_first_nonempty_stderr
- 10_parsing_hell/122_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 10_parsing_hell/12_stderr_minishell | other -> command_not_found |  | command not found
- 10_parsing_hell/14_stderr_minishell | other -> command_not_found |  | command not found
- 10_parsing_hell/15_stderr_minishell | other -> command_not_found |  | command not found
- 11_expansion/4_stderr_minishell | ambiguous_redirect -> enoent | $notexists: ambiguous redirect | open: No such file or directory
- 1_builtins_export/14_stderr_minishell | invalid_identifier -> other | export: `0': not a valid identifier | arg not valid
- 1_builtins_export/19_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 1_builtins_export/20_stderr_minishell | invalid_identifier -> other | export: `===': not a valid identifier | arg not valid
- 1_builtins_export/21_stderr_minishell | invalid_identifier -> other | export: `===': not a valid identifier | arg not valid
- 1_builtins_export/22_stderr_minishell | invalid_identifier -> other | export: `TE-ST=100': not a valid identifier | arg not valid
- 1_builtins_export/23_stderr_minishell | invalid_identifier -> other | export: `TEST-=100': not a valid identifier | arg not valid
- 1_builtins_export/25_stderr_minishell | invalid_identifier -> other | export: `==========': not a valid identifier | arg not valid
- 1_builtins_export/26_stderr_minishell | invalid_identifier -> other | export: `1TEST=': not a valid identifier | arg not valid
- 1_builtins_export/27_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 1_builtins_export/29_stderr_minishell | invalid_identifier -> other | export: `TE+S=T=': not a valid identifier | arg not valid
- 1_builtins_export/30_stderr_minishell | invalid_identifier -> other | export: `TES.T=123': not a valid identifier | arg not valid
- 1_builtins_export/31_stderr_minishell | invalid_identifier -> other | export: `TES.T=123': not a valid identifier | arg not valid
- 1_builtins_export/32_stderr_minishell | invalid_identifier -> other | export: `TES+T=123': not a valid identifier | arg not valid
- 1_builtins_export/34_stderr_minishell | invalid_identifier -> other | export: `TES}T=123': not a valid identifier | arg not valid
- 1_builtins_export/35_stderr_minishell | invalid_identifier -> other | export: `TES{T=123': not a valid identifier | arg not valid
- 1_builtins_export/36_stderr_minishell | invalid_identifier -> other | export: `TES-T=123': not a valid identifier | arg not valid
- 1_builtins_export/3_stderr_minishell | invalid_identifier -> other | export: `=============123': not a valid identifier | arg not valid
- 1_builtins_export/40_stderr_minishell | invalid_identifier -> other | export: `TE*ST=123': not a valid identifier | arg not valid
- 1_builtins_export/41_stderr_minishell | invalid_identifier -> other | export: `TES#T=123': not a valid identifier | arg not valid
- 1_builtins_export/42_stderr_minishell | invalid_identifier -> other | export: `TES@T=123': not a valid identifier | arg not valid
- 1_builtins_export/43_stderr_minishell | invalid_identifier -> other | export: `TES!T=123': not a valid identifier | arg not valid
- 1_builtins_export/45_stderr_minishell | invalid_identifier -> other | export: `=============123': not a valid identifier | arg not valid
- 1_builtins_export/46_stderr_minishell | invalid_identifier -> other | export: `+++++++=123': not a valid identifier | arg not valid
- 1_builtins_export/48_stderr_minishell | invalid_identifier -> other | export: `TES^T=123': not a valid identifier | arg not valid
- 1_builtins_export/49_stderr_minishell | invalid_identifier -> other | export: `TES!T=123': not a valid identifier | arg not valid
- 1_builtins_export/50_stderr_minishell | invalid_identifier -> other | export: `TES~T=123': not a valid identifier | arg not valid
- 1_builtins_export/53_stderr_minishell | invalid_identifier -> other | export: `?=hallo': not a valid identifier | arg not valid
- 1_builtins_export/54_stderr_minishell | invalid_identifier -> other | export: `0=hallo': not a valid identifier | arg not valid
- 1_builtins_export/5_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 1_builtins_export/6_stderr_minishell | invalid_identifier -> other | export: `=42': not a valid identifier | arg not valid
- 1_builtins_export/7_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 1_builtins_export/8_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 1_pipelines/25_stderr_minishell | other -> command_not_found |  | command not found
- 1_pipelines/26_stderr_minishell | other -> command_not_found |  | command not found
- 1_pipelines/27_stderr_minishell | other -> command_not_found |  | command not found
- 1_pipelines/28_stderr_minishell | other -> command_not_found |  | command not found
- 1_pipelines/29_stderr_minishell | other -> command_not_found | warning: here-document at line 11 delimited by end-of-file (wanted `stop3') | command not found
- 1_pipelines/30_stderr_minishell | other -> command_not_found |  | command not found
- 1_pipelines/33_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 1_redirs/80_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/81_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/82_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/83_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/84_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/85_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/86_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/87_stderr_minishell | other -> command_not_found |  | command not found
- 1_redirs/88_stderr_minishell | other -> command_not_found |  | command not found
- 1_scmds/25_stderr_minishell | command_not_found -> perm_denied | .: command not found | execve: Permission denied
- 1_scmds/36_stderr_minishell | is_directory -> perm_denied | /bin/: Is a directory | execve: Permission denied
- 1_scmds/40_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 1_scmds/41_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 2_correction/100_stderr_minishell | other -> command_not_found |  | command not found
- 2_correction/102_stderr_minishell | other -> command_not_found |  | command not found
- 2_correction/76_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 2_correction/77_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 2_correction/78_stderr_minishell | invalid_identifier -> other | export: `=': not a valid identifier | arg not valid
- 2_correction/80_stderr_minishell | invalid_identifier -> other | export: `=============123': not a valid identifier | arg not valid
- 2_correction/99_stderr_minishell | other -> command_not_found |  | command not found
- 2_path_check/14_stderr_minishell | enoent -> command_not_found | ls: No such file or directory | command not found
- 8_syntax_errors/10_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/11_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<<' | syntax error
- 8_syntax_errors/12_stderr_minishell | is_directory -> perm_denied | /home/immanuel: Is a directory | execve: Permission denied
- 8_syntax_errors/13_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/14_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/15_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/17_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/18_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/19_stderr_minishell | command_not_found -> perm_denied | .: command not found | execve: Permission denied
- 8_syntax_errors/1_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/20_stderr_minishell | command_not_found -> perm_denied | ..: command not found | execve: Permission denied
- 8_syntax_errors/21_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/24_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/25_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/26_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/27_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/29_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/2_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/30_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/31_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/32_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/33_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/34_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/37_stderr_minishell | is_directory -> perm_denied | /: Is a directory | execve: Permission denied
- 8_syntax_errors/39_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/3_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `newline' | syntax error
- 8_syntax_errors/41_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/42_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/43_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/47_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/48_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/49_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/4_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/50_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/51_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/52_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/53_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/54_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/55_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/56_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/57_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/58_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/59_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/5_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>>' | syntax error
- 8_syntax_errors/60_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/61_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/62_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/63_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/64_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/65_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/66_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/67_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/68_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>>' | syntax error
- 8_syntax_errors/69_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/6_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>>' | syntax error
- 8_syntax_errors/70_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/71_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/72_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/73_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/74_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/75_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/76_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/77_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/78_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/79_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/7_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/80_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/81_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/82_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/83_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/84_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/85_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/86_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/87_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/88_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>>' | syntax error
- 8_syntax_errors/89_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<' | syntax error
- 8_syntax_errors/8_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>>' | syntax error
- 8_syntax_errors/90_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/91_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<<' | syntax error
- 8_syntax_errors/92_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<<' | syntax error
- 8_syntax_errors/93_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `|' | syntax error
- 8_syntax_errors/94_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/95_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `>' | syntax error
- 8_syntax_errors/9_stderr_minishell | syntax_unexpected_token -> syntax_generic | syntax error near unexpected token `<<' | syntax error
