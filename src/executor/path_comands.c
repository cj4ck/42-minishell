/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_comands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 23:30:32 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/17 14:31:45 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pc_search_in_path(t_env *env, t_command com)
{
	char		*bin_path;
	char		**path;
	char		*tmp;
	int			ret_val;

	if (com.command[0] == '.' || com.command[0] == '/')
	{
		bin_path = pc_find_script(com.command, env);
		return (pc_execute_path(bin_path, env, com));
	}
	tmp = pc_get_env_var(env, "PATH");
	if (!tmp)
		return (127);
	path = ft_split(tmp, ':');
	free(tmp);
	bin_path = 0;
	ret_val = pc_find_binary(env, com, bin_path, path);
	if (ret_val == 127)
	{
		ft_putstr_fd("Unrecognized command\n", 2);
		pc_clear_2d_tab(path);
	}
	return (ret_val);
}

int	pc_find_binary(t_env *env, t_command com, char *bin_path, char **path)
{
	struct stat	file;
	int			i;

	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_pathjoin(path[i], com.command);
		if (lstat(bin_path, &file) != -1)
		{
			pc_clear_2d_tab(path);
			if (pc_check_permision(file))
				return (pc_execute_path(bin_path, env, com));
		}
		else
			free(bin_path);
	}
	return (127);
}

int	pc_check_permision(struct stat file)
{
	if ((file.st_mode > 0) && (S_IEXEC & file.st_mode) && S_ISREG(file.st_mode))
	{
		if (file.st_mode & S_IXUSR)
			return (1);
		else
			ft_putstr_fd("File is not executable", 2);
	}
	else
		ft_putstr_fd("This is not a file", 2);
	return (0);
}

int	pc_execute_path(char *bin_path, t_env *env, t_command com)
{
	pid_t	pid;
	int		result;
	char	**argv;

	pid = fork();
	argv = 0;
	result = 0;
	pc_proc_signal_handler();
	if (pid == 0)
	{
		argv = pc_change_command_to_argv(com);
		result = execve(bin_path, argv, env->env_var);
	}
	else if (pid < 0)
	{
		free(bin_path);
		ft_putstr_fd("Fork failed", 2);
		return (-1);
	}
	wait(&result);
	free(bin_path);
	pc_clear_2d_tab(argv);
	env->last_result = result;
	return (result);
}

char	**pc_change_command_to_argv(t_command com)
{
	char	**argv;
	int		i;
	int		j;

	i = 0;
	while (com.arguments[i])
		i++;
	argv = malloc(sizeof(char *) * (i + 3));
	i = 0;
	argv[i] = ft_strdup(com.command);
	if (com.flags)
		argv[++i] = ft_strjoin("-", com.flags);
	j = 0;
	if (com.arguments)
	{
		while (com.arguments[j])
		{
			argv[++i] = ft_strdup(com.arguments[j++]);
		}
	}
	argv[++i] = 0;
	return (argv);
}
