/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:11:54 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/17 14:19:44 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pc_input_validation(char **input)
{
	char		**splited_input;
	int			i;
	int			j;
	int			only_spaces;

	pc_escape_pipe(input);
	splited_input = ft_split(*input, '|');
	splited_input = pc_unescape_pipe(splited_input);
	i = 0;
	while (splited_input[i])
	{
		j = 0;
		only_spaces = 1;
		while (splited_input[i][j])
		{
			if (splited_input[i][j++] != ' ')
				only_spaces = 0;
		}
		if (only_spaces)
			return (0);
		i++;
	}
	return (splited_input);
}

void	pc_escape_pipe(char **input)
{
	int	i;
	int	j;

	i = 0;
	while ((*input)[i])
	{
		if (pc_is_quote((*input)[i]))
		{
			j = i + 1;
			while ((*input)[j] != (*input)[i] && (*input)[j])
			{
				if ((*input)[j] == '|')
					(*input)[j] = 1;
				j++;
			}
			i = j + 1;
		}
		else
			i++;
	}
}

char	**pc_unescape_pipe(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == 1)
				input[i][j] = '|';
			j++;
		}
		i++;
	}
	return (input);
}

int	pc_count_args(char *str_com, int i)
{
	int		j;
	int		result;

	result = 0;
	while (str_com && str_com[i])
	{
		j = 1;
		if (pc_is_quote(str_com[i]))
		{
			while (str_com[i + j] != str_com[i] && str_com[i + j])
				j++;
			result++;
		}
		else
		{
			while (str_com[i + j] != ' ' && str_com[i + j])
				j++;
			result++;
		}
		while ((--j + 2) && str_com[i])
			i++;
	}
	return (result);
}

void	pc_add_arg(t_command *command, int *k, char *arg)
{
	if (arg[0] != 0)
		command->arguments[(*k)++] = arg;
	else
		free(arg);
}
