/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commad_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:54:23 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/17 14:26:39 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*pc_get_command_table(char **input)
{
	char		**splited_input;
	t_command	*com_tab;
	int			i;

	splited_input = pc_input_validation(input);
	if (!splited_input)
		return (0);
	com_tab = malloc(sizeof(t_command)
			* (ft_get_number_of_words(*input, '|') + 1));
	i = 0;
	while (splited_input[i])
	{
		com_tab[i].command = 0;
		com_tab[i].flags = 0;
		com_tab[i].arguments = 0;
		pc_get_command(splited_input[i], &(com_tab[i]));
		i++;
	}
	com_tab[i].command = 0;
	pc_clear_2d_tab(splited_input);
	return (com_tab);
}

void	pc_get_command(char *str_com, t_command *command)
{
	int		i;

	i = 0;
	if (str_com[i] == ' ')
		str_com++;
	while (str_com[i] && str_com[i] != ' ')
		i++;
	command->command = ft_substr(str_com, 0, i);
	command->fd[0] = 0;
	command->fd[1] = 1;
	command->arguments = malloc(sizeof(char *)
			* (pc_count_args(str_com, i) + 1));
	command->arguments[0] = 0;
	if (!str_com[i] || !str_com[i + 1])
		return ;
	i++;
	pc_update_command_data(str_com, command, i);
}

void	pc_update_command_data(char *str_com, t_command *command, int i)
{
	int		j;
	int		k;

	k = 0;
	while (str_com[i])
	{
		j = 1;
		if (str_com[i] == '-' && str_com[i + 1] && ft_isalpha(str_com[i + 1]))
			pc_update_flags(str_com, command, i, &j);
		else if (pc_is_quote(str_com[i]))
			j = pc_update_quote_arg(command, str_com, i, &k);
		else
		{
			while (str_com[i + j] != ' ' && str_com[i + j])
				j++;
			pc_add_arg(command, &k, ft_substr(str_com, i, j));
		}
		while ((--j + 2) && str_com[i])
			i++;
	}
	command->arguments[k] = 0;
}

void	pc_update_flags(char *str_com, t_command *command, int i, int *j)
{
	char	*tmp;
	char	*tmp2;

	while (str_com[i + *j] != ' ' && str_com[i + *j])
		(*j)++;
	if (command->flags)
	{
		tmp2 = ft_substr(str_com, i + 1, (*j) - 1);
		tmp = ft_strjoin(command->flags, tmp2);
		free(command->flags);
		free(tmp2);
		command->flags = tmp;
	}
	else
		command->flags = ft_substr(str_com, i + 1, (*j) - 1);
}

int	pc_update_quote_arg(t_command *command, char *str_com, int i, int *k)
{
	int	j;

	j = 1;
	while (str_com[i + j] != str_com[i])
		j++;
	if (str_com[i] == str_com[i + 1] && j++)
		command->arguments[(*k)++] = ft_strdup("\0");
	else
		pc_add_arg(command, k, ft_substr(str_com, i + 1, j++ - 1));
	return (j);
}
