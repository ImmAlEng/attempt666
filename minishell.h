#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_status;

enum				e_redir
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND,
	R_MAX
};

enum				e_err
{
	ERR_AMBIGOUS,
	ERR_SYNTAX,
	ERR_FILE,
	ERR_MAX
};

typedef struct s_expand
{
	char			*str;
	char			*name;
	char			*val;
	char			*start;
	char			*stop;
	size_t			first_q;
}					t_expand;

typedef struct s_ifs
{
	bool			lead_sep;
	bool			trail_sep;
	t_dlist			*fields;
}					t_ifs;

typedef struct s_redir
{
	enum e_redir	type;
	char			*target;
	bool			quoted;
	t_dlist			*tokens;
}					t_redir;

typedef struct s_cmd
{
	enum e_err		err;
	char			*cmd;
	char			**argv;
	t_dlist			*redirs;
	t_dlist			*tokens;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	int				her_pipe[2];
	int				n_heredoc;
	bool			has_heredoc;
	bool			is_builtin;
	bool			needs_fork;
	int				exit_status;
}					t_cmd;

typedef struct s_data
{
	char			*line;
	t_dlist			*pipeline;
	t_cmd			**cmds;
	size_t			n_cmds;
	char			**env;
	bool			err[ERR_MAX];
	bool			abandon;
	bool			quit;
	bool			malloc_err;
}					t_data;

/*		signals		*/
void				ft_setup_signals(void);
void				ft_reset_signals(void);

/*		my shit		*/
int					ft_cmds_distro(t_data *data);
void				ft_cmds_check(t_data *data);
void				ft_has_heredoc(t_cmd *cmd);
bool				ft_is_builtin(t_cmd *cmd);

/*		pipeline	*/
int					ft_exec_pipeline(t_data *data);
int					ft_run_pipeline(t_data *data, int i, int *status,
						char *path);
void				ft_wait_kiddo(t_data *data, int *status);

/*		pipes		*/
bool				ft_create_pipes(t_data *data);
void				ft_close_pipes(t_data *data);
void				ft_handle_pipes(t_data *data, int i);

/*		builtin		*/
int					ft_exec_builtin(t_data *data, int i);
int					ft_run_builtin(t_data *data, int i);

/*		external	*/
int					ft_exec_external(t_data *data);
char				*ft_find_binary(t_data *data, int c_i);
char				*ft_get_path_env(t_data *data);
char		*ft_get_path_exec(t_data *data, char **dirs, char *cmd, int i);
		// added strcpy and strcat into libft

/*		redir		*/
bool				ft_handle_redirs(t_cmd *cmd);
bool				ft_redir_in(t_cmd *cmd, char *target);
bool				ft_redir_out(t_cmd *cmd, char *target);
bool				ft_redir_app(t_cmd *cmd, char *target);

/*		heredoc		*/
void				ft_exec_heredoc(t_data *data, int c_i);
void	ft_redir_her(t_data *data, int c_i, char *del, bool quoted);
		// added strcmp into libft
void				ft_heredoc_loop(t_data *data, int c_i, char *del,
						bool quoted);
void				ft_close_heredoc(t_data *data);

/*		erlöse mich		*/
char				*ft_heredoc_expand(t_data *data, char *line);

/*		err msgs	*/
int					ft_error_messages(enum e_err error, char *str);
void				ft_err_with_arg(const char *arg, const char *suffix);
void				ft_perror_arg(const char *arg);

/*		echo		*/
int					ft_echo(t_cmd *cmd);
bool				ft_n_flag(char *str);

/*		pwd and env		*/
int					ft_pwd(void);
int					ft_env(t_data *data, int c_i);

/*		unset		*/
int					ft_unset(t_data *data, int cmd_i);
char				**ft_remove_var(char **env, int env_i);
bool				ft_env_cleanup(char **env, int env_i);

/*		export		*/
int					ft_export(t_data *data, int cmd_i);

int					ft_print_export_var(char **env);
int					ft_actual_export_print(char **env);
char				**ft_sort_env(char **env);
char				**ft_bubble_sort(char **env);
int					ft_cmp_export(char *s1, char *s2);

bool				ft_export_valid(char *argv);
int					ft_var_present(t_data *data, char *argv);
bool				ft_modify_var(t_data *data, char *argv, int env_i);
bool				ft_add_var(t_data *data, char *argv);
char				**ft_actual_export(t_data *data, char *argv);
bool				ft_update_underscore(t_data *data, t_cmd *cmd);

/*		cd			*/
int					ft_cd(t_data *data, int cmd_i);
int					ft_cd_home(t_data *data);
int					ft_cd_with_arg(t_data *data, int cmd_i);
char				*ft_home_path(t_data *data);

int					ft_handle_pwds(t_data *data);
bool				ft_update_oldpwd(t_data *data, int cur_pwd, int old_pwd);
bool				ft_update_pwd(t_data *data, int cur_pwd);

/*		ur shit		*/
bool				ft_tokenize(t_data *data);

/*		ft_free.c			*/
void				ft_free_data(t_data **data);
void				ft_close_if(int *fd);
void				ft_free_cmds(t_data *data);
void				ft_free_redirs(t_dlist **redirs);

/*		ft_redir_init.c		*/
bool				ft_redir_init(t_cmd *cmd, t_dlist **tokens);
bool				ft_cmds_create(t_data *data);

/*		ft_is.c			*/
enum e_redir		ft_get_redir_type(char *str);
bool				ft_is_pipe(char *str);
bool				ft_is_redir(char *str);
bool				ft_is_operator(char *str);

/*		ft_cmds_init.c		*/
bool				ft_init_cmds(t_data *data);

/*		ft_ifs_and_superglue.c	*/

t_ifs				*ft_create_ifs(char *value);
bool				ft_insert_after(t_dlist *at, const char *s, t_dlist **newn);
void				ft_free_ifs(t_ifs *ifs);
bool				ft_replace_content(t_dlist *tok, char *newc);
bool				ft_expand_nq(t_expand *e, t_data *data, t_dlist **tokens);
bool				ft_superglue_ifs(t_dlist **tok, char *value, size_t start,
						char **stop);

/*		ft_remove_quotes.c	*/
bool				ft_remove_quotes(char *q, t_expand *e, t_dlist **tokens,
						char c);

/*		ft_getenv.c	*/
char				*ft_getenv(char *name, char **env);
char				*ft_get_varname(char *str, char **end);
bool				ft_should_expand_dollar(char *dollar);

/*		ft_expand_dq.c		*/
bool				ft_expand_dq(t_expand *e, t_data *data, t_dlist **tok);

/*		exit		*/
int					ft_exit(t_data *data, int cmd_i);
void				ft_free_exit(t_data *data, int c_i);
int					ft_cleanup_runtime(t_data **data);

/*		ft_match_found.c	*/
bool				ft_match_found(char *c);

/*		ft_expander.c	*/
bool				ft_expander(t_data *data);

/*		ft_convert_token.c	*/
bool				ft_direct_token_pointers(t_data *data);

/*		DEBUG			*/
void				ft_print_data(t_data *data);
/*		DEBUG			*/

#endif
