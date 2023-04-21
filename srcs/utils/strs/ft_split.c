/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:09:06 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/11 14:58:55 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/ft_strings.h"

char	**rec_split(char **splited, int words, char *c, const char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str && *str && s().contains_char(c, *str))
		str++;
	while (str && str[i] && !s().contains_char(c, str[i]))
		i++;
	word = NULL;
	if (i)
	{
		word = ft_calloc(i + 1);
		while (*str && !s().contains_char(c, *str))
			*word++ = *str++;
	}
	if (word)
		splited = rec_split(splited, words + 1, c, str);
	else if (!*str)
		splited = ft_calloc(sizeof(char *) * (words + 1));
	splited[words] = word - i;
	return (splited);
}

char	**ft_split(const char *str, char *c)
{
	return (rec_split(0, 0, c, str));
}
