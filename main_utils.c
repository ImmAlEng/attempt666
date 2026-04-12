/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:57:24 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:58:28 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_handle_syntax_error(t_data *data)
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

int	ft_process_prompt_line(t_data *data)
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
	if (ft_has_ambiguous_redirect(data->cmds))
	{
		ft_error_messages(ERR_AMBIGOUS, "");
		g_exit_status = 1;
		if (ft_cleanup_runtime(&data))
			return (0);
		return (1);
	}
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
