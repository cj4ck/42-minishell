/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exit_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:24:52 by cjackows          #+#    #+#             */
/*   Updated: 2023/06/17 14:47:05 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pc_cd_helper(t_command *com, char *home);

int	pc_cd(t_env *env, t_command com)
{
	char	*home;
	char	buffer[1024];
	int		ret_val;

	home = pc_get_env_var(env, "HOME");
	ret_val = pc_cd_helper(&com, home);
	pc_env_del_var(env, "PWD");
	pc_env_add_var(env, "PWD", getcwd(buffer, 1024));
	return (ret_val);
}

static int	pc_cd_helper(t_command *com, char *home)
{
	if (com->arguments[0] == NULL)
	{
		if (home == NULL)
		{
			ft_putstr_fd("The HOME variable is not set\n", 2);
			return (1);
		}
		if (chdir(home) != 0)
		{
			ft_putstr_fd("The HOME variable is not valid\n", 2);
			return (1);
		}
	}
	else
	{
		if (chdir(com->arguments[0]) != 0)
		{
			ft_putstr_fd("cd: No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	pc_exit(t_env *env, t_command com)
{
	int	result;

	if (com.arguments[0] == NULL)
	{
		pc_clear_env(env);
		exit(0);
	}
	if (com.arguments[0] && com.arguments[1])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	if (!ft_isnumber(com.arguments[0]) || ft_overlflow_int(com.arguments[0]))
	{
		ft_putstr_fd("Numeric argument is required\n", 2);
		return (255);
	}
	else
	{
		pc_clear_env(env);
		result = ft_atoi(com.arguments[0]);
		if (result < 0)
			exit(256 + result);
		exit(result);
	}
}

int	pc_export(t_env *env, t_command com)
{
	char	*tmp;
	char	*tmp2;
	int		tmp3;

	if (!com.arguments[0] || com.arguments[1])
		return (2);
	tmp3 = ft_strchrn(com.arguments[0], '=');
	if (!tmp3)
		return (3);
	tmp = ft_substr(com.arguments[0], 0, tmp3);
	pc_env_del_var(env, tmp);
	tmp2 = ft_substr(com.arguments[0], tmp3 + 1,
			ft_strlen(com.arguments[0]) - ft_strlen(tmp) - 1);
	pc_env_add_var(env, tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (0);
}

int	pc_unset(t_env *env, t_command com)
{
	char	*tmp;
	int		tmp2;

	if (!com.arguments[0] || com.arguments[1])
		return (2);
	tmp2 = ft_strchrn(com.arguments[0], '=');
	if (!tmp2)
		return (3);
	tmp = ft_substr(com.arguments[0], 0, tmp2);
	pc_env_del_var(env, tmp);
	free(tmp);
	return (0);
}
