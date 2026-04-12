/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:58:34 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:59:18 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline_signal_hook(void)
{
	if (g_exit_status == SIGINT)
	{
		g_exit_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

void	ft_sigint_handler(int sig)
{
	g_exit_status = sig;
	write(1, "\n", 1);
}

void	ft_setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_pipe;

	ft_bzero(&sa_int, sizeof(sa_int));
	sa_int.sa_handler = ft_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	ft_bzero(&sa_pipe, sizeof(sa_pipe));
	sa_pipe.sa_handler = SIG_IGN;
	sigemptyset(&sa_pipe.sa_mask);
	sigaction(SIGPIPE, &sa_pipe, NULL);
	rl_signal_event_hook = ft_readline_signal_hook;
}

void	ft_reset_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
}

int	ft_cleanup_runtime(t_data **data)
{
	if (!data || !*data)
		return (1);
	ft_free((void **)&(*data)->line);
	if ((*data)->cmds)
		ft_free_cmds(*data);
	(*data)->cmds = NULL;
	(*data)->pipeline = NULL;
	if ((*data)->quit || (*data)->malloc_err)
		return (1);
	return (0);
}
