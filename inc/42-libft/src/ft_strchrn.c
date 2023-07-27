/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:25:20 by cjackows          #+#    #+#             */
/*   Updated: 2023/06/09 15:01:25 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * @brief   function searches for the FIRST occurrence of 
 * character 'c' in string 's'.If 's' doesnt end with 
 * NULL program might cras!
 * @param s This is the string to be scanned.
 * @param c This is the character to be searched in 's'.
 * @return char* Returns a index of the first 
 * occurrence of c that is converted to a character in string.
 * The function returns NULL if the specified character is not found.
 */
int	ft_strchrn(char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

// 	int	main(void)
// 	{
// 	char	str[] = "lol111111111111o";
// 	int	ch = 'o';
// 	char	*ach;
// 	ach = ft_strrchr(str, ch);
// 	if (ach == NULL)
// 		printf ("We didn't find it\n");
// 	else
// 		printf ("We found it on position - %ld\n", (ach-str+1));
// 	return (0);
// }
