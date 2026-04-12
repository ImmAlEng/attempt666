# TODO April

## NORMINETTE
- [ ] Change files to fit NORMINETTE. !!!
- [ ] Re-run symbol check: no disallowed non-`ft_` function calls in final `minishell` binary.

## Regression Checks
- [ ] Verify `exit` behavior parity:
  - [ ] `exit`
  - [ ] `exit 42`
  - [ ] `exit -1`
  - [ ] `exit 9223372036854775807`
  - [ ] `exit 9223372036854775808` (numeric argument required)
  - [ ] `exit -9223372036854775808`
  - [ ] `exit -9223372036854775809` (numeric argument required)
  - [ ] `exit 1 2` (too many arguments)

## Next Fixing Priorities
- [ ] Resolve remaining non-semantic stderr differences.
- [ ] Resolve remaining stdout mismatches in pipeline-heavy cases.
- [ ] Resolve remaining exit-code mismatches where one side is zero and the other non-zero.

## Notes
REMAINING TESTCASES ARE IN 
/mstest_output_2026-04-12_04.31.24/report_moved_***.md