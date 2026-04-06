#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "test.h"

#define MINISHELL_BIN "./minishell_test"

static int	s_passed;
static int	s_failed;

static char	*run_minishell(const char *input)
{
	int		pin[2];
	int		pout[2];
	pid_t	pid;
	char	*buf;
	size_t	total;
	ssize_t	n;
	char	tmp[4096];

	if (pipe(pin) || pipe(pout))
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		close(pin[1]);
		close(pout[0]);
		dup2(pin[0], STDIN_FILENO);
		dup2(pout[1], STDOUT_FILENO);
		close(pin[0]);
		close(pout[1]);
		execl(MINISHELL_BIN, MINISHELL_BIN, NULL);
		_exit(127);
	}
	close(pin[0]);
	close(pout[1]);
	write(pin[1], input, strlen(input));
	close(pin[1]);
	buf = NULL;
	total = 0;
	while ((n = read(pout[0], tmp, sizeof(tmp))) > 0)
	{
		buf = realloc(buf, total + (size_t)n + 1);
		memcpy(buf + total, tmp, (size_t)n);
		total += (size_t)n;
	}
	close(pout[0]);
	waitpid(pid, NULL, 0);
	if (buf)
		buf[total] = '\0';
	else
		buf = strdup("");
	return (buf);
}

void	check(const char *name, const char *input, const char *expected)
{
	char	*got;
	int		ok;

	got = run_minishell(input);
	ok = (got && strcmp(got, expected) == 0);
	if (ok)
	{
		printf("\033[0;32mPASS\033[0m  %s\n", name);
		s_passed++;
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m  %s\n", name);
		printf("      expected: |%s|\n", expected);
		printf("      got:      |%s|\n", got ? got : "(null)");
		s_failed++;
	}
	free(got);
}

int	summary(void)
{
	printf("\n=== %d passed, %d failed ===\n\n", s_passed, s_failed);
	return (s_failed);
}
