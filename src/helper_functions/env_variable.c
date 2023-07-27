/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:31:32 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/13 14:14:10 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pc_copy_env_variables(t_env *env, char **env_var)
{
	int	size;
	int	i;

	size = 0;
	while (env_var[size])
		size++;
	env->env_var = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env_var[i])
	{
		env->env_var[i] = ft_strdup(env_var[i]);
		i++;
	}
	env->env_var[i] = 0;
}

char	*pc_get_env_var(t_env *env, char *name)
{
	int			i;
	size_t		tmp;

	i = 0;
	while (env->env_var[i])
	{
		tmp = ft_strchrn(env->env_var[i], '=');
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& tmp == ft_strlen(name))
		{
			return (ft_strdup(env->env_var[i] + tmp + 1));
		}
		i++;
	}
	return (0);
}

void	pc_env_add_var(t_env *env, char *name, char *val)
{
	int		size;
	int		i;
	char	**result;
	char	*tmp;

	size = 0;
	while (env->env_var[size])
		size++;
	result = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (env->env_var[i])
	{
		result[i] = ft_strdup(env->env_var[i]);
		i++;
	}
	tmp = ft_strjoin(name, "=");
	result[i] = ft_strjoin(tmp, val);
	free(tmp);
	result[++i] = 0;
	pc_clear_2d_tab(env->env_var);
	env->env_var = result;
}

void	pc_env_del_var(t_env *env, char *name)
{
	int		size;
	int		i;
	int		j;
	char	**result;
	int		tmp;

	size = 0;
	while (env->env_var[size])
		size++;
	result = (char **)malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (env->env_var[++i])
	{
		tmp = ft_strchrn(env->env_var[i], '=');
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& (size_t)tmp == ft_strlen(name))
			continue ;
		result[j] = ft_strdup(env->env_var[i]);
		j++;
	}
	result[j] = 0;
	pc_clear_2d_tab(env->env_var);
	env->env_var = result;
}
