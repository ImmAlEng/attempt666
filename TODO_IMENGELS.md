# TODO April

## Compliance
- [x] Replace disallowed `strtoll` usage in exit parsing with `ft_strtoll`.
- [x] Add `ft_strtoll` declaration to `libft/libft.h`.
- [x] Add `libft/srcs/ft_strtoll.c` to `libft/Makefile` sources.
- [ ] Ensure all custom files pass Norminette (including headers in project `.c` files).
- [ ] Re-run symbol check: no disallowed non-`ft_` function calls in final `minishell` binary.

## Regression Checks
- [ ] Rebuild from clean state: `make fclean && make`.
- [ ] Verify `exit` behavior parity:
  - [ ] `exit`
  - [ ] `exit 42`
  - [ ] `exit -1`
  - [ ] `exit 9223372036854775807`
  - [ ] `exit 9223372036854775808` (numeric argument required)
  - [ ] `exit -9223372036854775808`
  - [ ] `exit -9223372036854775809` (numeric argument required)
  - [ ] `exit 1 2` (too many arguments)

## Tester Output Hygiene
- [x] Split report rows by failure pattern into dedicated files.
- [x] Aggregate valgrind outputs into one file.
- [x] Aggregate stdout outputs into one file.
- [x] Aggregate stderr outputs for report stderr-fail entries.
- [ ] Keep only actionable report buckets for next fixing cycle.

## Valgrind / FD Status
- [x] Confirm no non-zero valgrind error summaries in merged run output.
- [x] Confirm no definitely/indirectly/possibly-lost bytes reported.
- [x] Confirm no fd >= 4 left open at exit in merged valgrind output.
- [ ] Re-check after next code changes.

## Next Fixing Priorities
- [ ] Resolve remaining non-semantic stderr differences.
- [ ] Resolve remaining stdout mismatches in pipeline-heavy cases.
- [ ] Resolve remaining exit-code mismatches where one side is zero and the other non-zero.

## Notes
- `testsuite/` should stay ignored unless explicitly requested.
- Prefer focused fixes with immediate retest and valgrind re-check.
