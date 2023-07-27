/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:18:41 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/12 00:03:15 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pc_check_quote(char **input, int i, char *quote)
{
	if (*quote == '\0' && pc_is_quote((*input)[i]))
	{
		*quote = (*input)[i];
	}
	else if (*quote == (*input)[i])
	{
		*quote = '\0';
	}
}

void	pc_trimming(char **input, char *quote, char	**result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*quote = '\0';
	while ((*input)[i] && pc_is_to_trim((*input)[i]))
		i++;
	while ((*input)[i])
	{
		while ((*input)[i] && (!pc_is_to_trim((*input)[i]) || *quote))
		{
			pc_check_quote(input, i, quote);
			(*result)[j] = (*input)[i];
			j++;
			i++;
		}
		while ((*input)[i] && pc_is_to_trim((*input)[i]))
			i++;
		if ((*input)[i])
			(*result)[j++] = ' ';
	}
	(*result)[j] = '\0';
}

int	pc_is_to_trim(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	pc_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	pc_is_quote_closed(char *str, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}
