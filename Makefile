CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -MP -MMD
RLFLAGS = -lreadline

NAME    = minishell

SRCS    = ft_cmds_init.c \
	ft_expand_dq.c \
	ft_expander.c \
	ft_free.c \
	ft_getenv.c \
	ft_gloabal.c \
	ft_ifs.c \
	ft_is.c \
	ft_match_found.c \
	ft_pipeline.c \
	ft_redir_init.c \
	ft_redir_init_utils.c \
	ft_remove_quotes.c \
	ft_superglue_ifs.c \
	ft_free_cmds.c \
	ft_convert_tokens.c \
	main.c \
	main_utils.c \
	main_utils_2.c \
	ft_cmds_distro.c \
	ft_cmds_distro_utils.c \
	ft_exec_builtin.c \
	ft_exec_external.c \
	ft_exec_external_utils.c \
	ft_exec_pipeline.c \
	ft_exec_pipeline_utils.c \
	ft_handle_pipes.c \
	ft_handle_redirs.c \
	ft_exec_heredoc.c \
	ft_exec_heredoc_utils.c \
	ft_heredoc_expand.c \
	ft_echo.c \
	ft_pwd.c \
	ft_unset.c \
	ft_export.c \
	ft_export_print.c \
	ft_export_utils.c \
	ft_cd.c \
	ft_cd_utils.c \
	ft_my_strtoll.c \
	ft_exit.c \
	ft_err_msgs.c \
	ft_error_checks.c

OBJS        = $(SRCS:.c=.o)
DEPS        = $(OBJS:.o=.d)

LIBFT   = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS) $(VAL_OBJS) $(VAL_DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re