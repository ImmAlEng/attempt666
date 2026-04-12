#include "minishell.h"

static int	ft_readline_signal_hook(void)
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

static void	ft_sigint_handler(int sig)
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

int	ft_cleanup_quit(t_data **data, bool malloc_err)
{
	rl_clear_history();
	ft_free_data(data);
	if (malloc_err)
		return (write(2, "minishell> SYSCALL ERROR: Malloc. Exiting\n", 42), 1);
	return (g_exit_status);
}

t_data	*ft_init_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)ac;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_bzero((void *)data, sizeof(t_data));
	data->env = ft_arrdup(env);
	if (!data->env)
		return (free(data), NULL);
	return (data);
}

static int	ft_handle_syntax_error(t_data *data)
{
	ft_dlstclear(&data->pipeline, free);
	data->pipeline = NULL;
	if (data->cmds)
		ft_free_cmds(data);
	data->cmds = NULL;
	ft_free((void **)&data->line);
	if (data->malloc_err)
		return (-1);
	ft_error_messages(ERR_SYNTAX, "");
	g_exit_status = 2;
	return (1);
}

static int	ft_process_prompt_line(t_data *data)
{
	data->abandon = false;
	if (data->line[0] != '\0')
		add_history(data->line);
	if (!ft_tokenize(data))
		return (ft_handle_syntax_error(data));
	if (!data->pipeline)
		return (ft_free((void **)&data->line), 1);
	if (!ft_cmds_create(data))
		return (ft_handle_syntax_error(data));
	if (!ft_expander(data))
		return (-1);
	if (!ft_direct_token_pointers(data))
		return (-1);
	g_exit_status = ft_cmds_distro(data);
	if (ft_cleanup_runtime(&data))
		return (0);
	return (1);
}

bool	ft_prompt(t_data *data)
{
	int	state;

	while (data && !data->malloc_err && !data->quit)
	{
		data->line = readline("minishell>");
		if (!data->line)
		{
			data->quit = true;
			break ;
		}
		state = ft_process_prompt_line(data);
		if (state < 0)
			return (false);
		if (state == 0)
			break ;
	}
	return (data && !data->malloc_err);
}

int	main(int ac, char **av, char **env)
{
	t_data *data;

	data = ft_init_data(ac, av, env);
	if (!data)
		return (ft_cleanup_quit(NULL, true));
	ft_setup_signals();
	if (ft_prompt(data))
		return (ft_cleanup_quit(&data, data->malloc_err));
	return (ft_cleanup_quit(&data, data->malloc_err));
}
