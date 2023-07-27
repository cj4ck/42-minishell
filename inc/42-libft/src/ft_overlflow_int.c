/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overlflow_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:19:15 by cjackows          #+#    #+#             */
/*   Updated: 2023/06/12 15:06:22 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * @brief   Function checks if parameter passed is a number accept 
 * one - or + on the beggining.
 * @param c Parameter that gets checked
 * @return Returns int 1 if parameter is a digit or 0 if it's not.
 */
int	ft_overlflow_int(char *str)
{
	int	value;
	int	i;
	int	digit;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (ft_isdigit(str[i]) && str[i + 1] == '\0')
		return (0);
	value = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			digit = str[i] - '0';
			if (value > (INT_MAX - digit) / 10)
				return (1);
			value = value * 10 + digit;
			i++;
		}
		else
			return (1);
	}
	return (0);
}
