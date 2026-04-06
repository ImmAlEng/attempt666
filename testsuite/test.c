#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int	main(void)
{
	const char	*user = getenv("USER");
	char		user_line[256];

	if (!user)
		user = "";
	snprintf(user_line, sizeof(user_line), "%s\n", user);

	printf("\n=== minishell test suite ===\n\n");

	/* heredoc: quoted delimiter strips quotes, no expansion */
	check("heredoc double-quoted delimiter, no expansion",
		"cat << \"eof\"\n$USER\neof\n",
		"$USER\n");
	check("heredoc single-quoted delimiter, no expansion",
		"cat << 'eof'\n$USER\neof\n",
		"$USER\n");

	/* heredoc: unquoted delimiter expands */
	check("heredoc unquoted delimiter, expands $USER",
		"cat << eof\n$USER\neof\n",
		user_line);
	check("heredoc unquoted, expands $?",
		"true\ncat << EOF\n$?\nEOF\n",
		"0\n");
	check("heredoc quoted, $? not expanded",
		"cat << 'EOF'\n$?\nEOF\n",
		"$?\n");

	/* heredoc: multi-line body */
	check("heredoc multi-line body",
		"cat << DELIM\nline one\nline two\nDELIM\n",
		"line one\nline two\n");

	/* echo */
	check("echo hello world",
		"echo hello world\n",
		"hello world\n");
	check("echo -n no newline",
		"echo -n hello\n",
		"hello");

	/* exit status */
	check("exit code after true",
		"true\necho $?\n",
		"0\n");
	check("exit code after false",
		"false\necho $?\n",
		"1\n");

	/* syntax errors: $? == 2, shell continues */
	check("syntax error: leading pipe sets $? to 2",
		"| ls\necho $?\n",
		"2\n");
	check("syntax error: trailing pipe sets $? to 2",
		"ls |\necho $?\n",
		"2\n");
	check("syntax error: double pipe sets $? to 2",
		"ls | | cat\necho $?\n",
		"2\n");
	check("syntax error: unclosed double quote sets $? to 2",
		"echo \"unclosed\necho $?\n",
		"2\n");
	check("syntax error: unclosed single quote sets $? to 2",
		"echo 'unclosed\necho $?\n",
		"2\n");
	check("syntax error: shell continues after leading pipe",
		"| ls\necho alive\n",
		"alive\n");
	check("syntax error: shell continues after trailing pipe",
		"ls |\necho alive\n",
		"alive\n");
	check("syntax error: shell continues after unclosed quote",
		"echo \"unclosed\necho alive\n",
		"alive\n");

	return (summary() != 0);
}
