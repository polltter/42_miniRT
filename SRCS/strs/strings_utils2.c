/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:38:24 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:55:59 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

int	__isalpha(int c)
{
	if ('_' == c)
		return (1);
	if (c < 65 || c > 122)
		return (0);
	if (c > 90 && c < 97)
		return (0);
	return (1);
}

int	__isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	__isal_num(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (!__isdigit(str[i]) && !__isalpha(str[i]))
			return (1);
	return (0);
}

char	*__append(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(s().len(str, 0) + 2);
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	return (new);
}
