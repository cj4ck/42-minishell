/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:56:14 by cjackows          #+#    #+#             */
/*   Updated: 2023/06/17 14:34:13 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <fcntl.h>

# include "color.h"
# include "libft.h"

# define MAX_COMMAND_LENGTH 1024
# define SHELL_PROMPT "PentaCode🐚 "
# define SHELL_SIGN "❯❯ "

typedef struct s_env
{
	char			**env_var;
	int				last_result;
}			t_env;

typedef struct s_command
{
	char	*command;
	char	*flags;
	char	**arguments;
	int		fd[2];
	int		pid;
}			t_command;

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

//     -[ env_variable.c ]-     //
void		pc_copy_env_variables(t_env *env, char **env_var);
char		*pc_get_env_var(t_env *env, char *name);
void		pc_env_add_var(t_env *env, char *name, char *val);
void		pc_env_del_var(t_env *env, char *name);

//      -[ termios.c ]         //
void		pc_mod_term_atributes_echoctl_on(void);
void		pc_mod_term_atributes_echoctl_off(void);

//        -[ parser.c ]-        //
t_command	*pc_parse_raw_input(t_env *env, char **input);

//        -[ exec.c ]-        //
int			pc_exec_commands(t_env *env, t_command *commands);

//        -[ exec_helper.c ]-        //
void		pc_create_pipes(t_command *commands, t_env *env);
void		pc_close_fds_main(t_command *commands);
void		pc_close_fds_child(t_command *commands, int i);
int			pc_wait_for_child_and_return_result(t_command *commands,
				t_env *env);
char		*pc_find_script(char *script, t_env *env);

//        -[ redirections.c ]-        //
void		pc_file_redirection_check(t_command *command);

//        -[ print.c ]-        //
void		pc_print_strings_tab(char **tab);
void		pc_print_command_table(t_command *commands);

//        -[ clear.c ]-        //
void		pc_clear_env(t_env *env);
void		pc_clear_2d_tab(char **tab);

//        -[ signals.c ]-        //
void		pc_signals_interactive(void);
void		pc_proc_signal_handler(void);

//        -[ parser_helper.c ]-        //
void		pc_check_quote(char **input, int i, char *quote);
void		pc_trimming(char **input, char *quote, char	**result);
int			pc_is_to_trim(char c);
int			pc_is_quote(char c);
int			pc_is_quote_closed(char *str, int n);

//        -[ input_validation.c ]-        //
char		**pc_input_validation(char **input);
void		pc_escape_pipe(char **input);
char		**pc_unescape_pipe(char **input);
int			pc_count_args(char *str_com, int i);
void		pc_add_arg(t_command *command, int *k, char *arg);

//        -[ command_table.c ]-        //
t_command	*pc_get_command_table(char **input);
void		pc_get_command(char *str_com, t_command *command);
void		pc_update_flags(char *str_com, t_command *command, int i, int *j);
void		pc_update_command_data(char *str_com, t_command *command, int i);
int			pc_update_quote_arg(t_command *command,
				char *str_com, int i, int *k);

//        -[ exit.c ]-        //
void		pc_quit(t_env *env, char *msg, int failure);

//        -[ buildins.c ]-        //
int			pc_echo(t_command com);
int			pc_pwd(t_env *env);
int			pc_env(t_env *env);

//        -[ buildins2.c ]-        //
int			pc_cd(t_env *env, t_command com);
int			pc_exit(t_env *env, t_command com);
int			pc_export(t_env *env, t_command com);
int			pc_unset(t_env *env, t_command com);

//        -[ path_commands.c ]-        //
int			pc_search_in_path(t_env *env, t_command com);
int			pc_check_permision(struct stat file);
int			pc_execute_path(char *bin_path, t_env *env, t_command com);
char		**pc_change_command_to_argv(t_command com);
int			pc_find_binary(t_env *env, t_command com, char *bin_path,
				char **path);
#endif
