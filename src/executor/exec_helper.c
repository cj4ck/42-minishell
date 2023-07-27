/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:25:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/17 14:21:08 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pc_create_pipes(t_command *commands, t_env *env)
{
	int	i;

	i = 0;
	while (commands[i].command)
	{
		if (pipe(commands[i].fd) < 0)
			pc_quit(env, "Filed to create a pipe\n", 2);
		i++;
	}
}

void	pc_close_fds_main(t_command *commands)
{
	int	i;

	i = 0;
	while (commands[i].command)
	{
		close(commands[i].fd[0]);
		close(commands[i].fd[1]);
		i++;
	}
}

void	pc_close_fds_child(t_command *commands, int i)
{
	int	j;

	j = 0;
	while (commands[j].command)
	{
		if (i != j)
			close(commands[j].fd[1]);
		if (i - 1 != j)
			close(commands[j].fd[0]);
		j++;
	}
}

int	pc_wait_for_child_and_return_result(t_command *commands, t_env *env)
{
	int	i;
	int	result;

	i = -1;
	while (commands[++i].command)
		wait(&result);
	if (commands[i - 1].pid == 0)
		return (env->last_result);
	return (WEXITSTATUS(result) % 255);
}

char	*pc_find_script(char *script, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	if (script[0] == '.')
	{
		tmp = ft_substr(script, 1, ft_strlen(script) - 1);
		tmp2 = pc_get_env_var(env, "PWD");
		result = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		return (result);
	}
	else
		return (script);
}
