/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:05:51 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/13 16:00:38 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pc_print_strings_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	pc_print_command_table(t_command *commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i].command)
	{
		ft_printf("\n[%i] command: |%s|  ", i, commands[i].command);
		ft_printf("(fds: in: %i out: %i)", commands[i].fd[0],
			commands[i].fd[1]);
		if (commands[i].flags)
			ft_printf(" with flags: |%s|", commands[i].flags);
		ft_printf("\nArguments:\n");
		j = 0;
		while (commands[i].arguments[j])
		{
			ft_printf("\t%i - %s\n", j, commands[i].arguments[j]);
			j++;
		}
		i++;
	}
}
