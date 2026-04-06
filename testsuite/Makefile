CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I..
LIBFT   = ../libft/libft.a
RLFLAGS = -lreadline

# Parent .o files — all except main.o and ft_exec_heredoc.o (replaced locally)
PARENT_OBJS = \
	../ft_cmds_init.o \
	../ft_expand_dq.o \
	../ft_expander.o \
	../ft_free.o \
	../ft_getenv.o \
	../ft_gloabal.o \
	../ft_ifs.o \
	../ft_is.o \
	../ft_match_found.o \
	../ft_minishell_printer.o \
	../ft_pipeline.o \
	../ft_redir_init.o \
	../ft_remove_quotes.o \
	../ft_sort_token.o \
	../ft_superglue_ifs.o \
	../ft_unquoted_expansion.o \
	../ft_free_cmds.o \
	../ft_convert_tokens.o \
	../ft_cmds_distro.o \
	../ft_exec_builtin.o \
	../ft_exec_external.o \
	../ft_exec_pipeline.o \
	../ft_handle_pipes.o \
	../ft_handle_redirs.o \
	../ft_heredoc_expand.o \
	../ft_echo.o \
	../ft_pwd.o \
	../ft_unset.o \
	../ft_export.o \
	../ft_export_print.o \
	../ft_export_utils.o \
	../ft_cd.o \
	../ft_cd_utils.o \
	../ft_err_msgs.o \
	../ft_exit.o

LOCAL_OBJS     = test_main.o test_heredoc.o
MINISHELL_TEST = minishell_test
TEST_BIN       = run_tests

.PHONY: all test clean fclean _parent

all: $(MINISHELL_TEST) $(TEST_BIN)

# Build the parent project first so all ../*.o files exist
_parent:
	$(MAKE) -C ..

$(MINISHELL_TEST): _parent $(LOCAL_OBJS)
	$(CC) $(CFLAGS) $(LOCAL_OBJS) $(PARENT_OBJS) $(RLFLAGS) $(LIBFT) -o $@

$(TEST_BIN): test.c test_runner.c test.h
	$(CC) $(CFLAGS) test.c test_runner.c -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	./$(TEST_BIN)

clean:
	rm -f $(LOCAL_OBJS)

fclean: clean
	rm -f $(MINISHELL_TEST) $(TEST_BIN)
