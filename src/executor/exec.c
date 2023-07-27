/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:23:32 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/16 17:26:33 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pc_exec_notfork_command(t_env *env, t_command command);
static int	pc_exec_fork_command(t_env *env, t_command command);
static void	pc_fork_child(t_env *env, t_command *commands, int i);

int	pc_exec_commands(t_env *env, t_command *commands)
{
	int	i;
	int	result;

	pc_create_pipes(commands, env);
	i = 0;
	while (commands[i].command)
	{
		result = pc_exec_notfork_command(env, commands[i]);
		commands[i].pid = 0;
		if (result == -1)
			pc_fork_child(env, commands, i);
		else
			env->last_result = result;
		i++;
	}
	pc_close_fds_main(commands);
	return (pc_wait_for_child_and_return_result(commands, env));
}

static int	pc_exec_notfork_command(t_env *env, t_command command)
{
	ft_str_tolower(command.command);
	if (ft_strncmp(command.command, "cd", ft_strlen(command.command)) == 0)
		return (pc_cd(env, command));
	if (ft_strncmp(command.command, "exit", ft_strlen(command.command)) == 0)
		return (pc_exit(env, command));
	if (ft_strncmp(command.command, "export", ft_strlen(command.command)) == 0)
		return (pc_export(env, command));
	if (ft_strncmp(command.command, "unset", ft_strlen(command.command)) == 0)
		return (pc_unset(env, command));
	return (-1);
}

static void	pc_fork_child(t_env *env, t_command *commands, int i)
{
	commands[i].pid = fork();
	if (commands[i].pid == -1)
		pc_quit(env, "Filed to create a fork\n", 2);
	if (commands[i].pid == 0)
	{
		pc_close_fds_child(commands, i);
		pc_file_redirection_check(&(commands[i]));
		if (commands[i + 1].command)
			dup2(commands[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(commands[i - 1].fd[0], STDIN_FILENO);
		env->last_result = pc_exec_fork_command(env, commands[i]);
		close(commands[i].fd[1]);
		if (i != 0)
			close(commands[i - 1].fd[0]);
		exit(env->last_result % 255);
	}
}

static int	pc_exec_fork_command(t_env *env, t_command command)
{
	ft_str_tolower(command.command);
	if (ft_strncmp(command.command, "echo", ft_strlen(command.command)) == 0)
		return (pc_echo(command));
	if (ft_strncmp(command.command, "pwd", ft_strlen(command.command)) == 0)
		return (pc_pwd(env));
	if (ft_strncmp(command.command, "env", ft_strlen(command.command)) == 0)
		return (pc_env(env));
	return (pc_search_in_path(env, command));
}
