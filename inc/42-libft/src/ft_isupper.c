/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:20:56 by cjackows          #+#    #+#             */
/*   Updated: 2023/06/12 13:15:46 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * @brief Return 1 if c is in uppercase.
 * @param c Character that gets checked.
 * @return Return 1 if c is in uppercase.
 */
int	ft_isupper(int c)
{
	return ((c >= 'A') && (c <= 'Z'));
}
