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

int	__str_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		++i;
	return (i);
}

int	__strn_cmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = -1;
	if (!str1 || !str2)
		return (1);
	while (++i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}

int	__strn_str(const char *haystack, const char *needle)
{
	int	i;
	int	size_small;
	int	size_big;

	if (!needle || !haystack)
		return (0);
	i = -1;
	size_small = __str_len(needle, 0);
	size_big = __str_len(haystack, 0);
	if (size_big >= size_small)
	{
		while (++i <= size_big - size_small)
		{
			if (!__strn_cmp(&haystack[i], needle, size_small))
				return (1);
		}
	}
	return (0);
}

static size_t	check_size(const char *str)
{
	int	size;
	int	i;

	if (!str)
		return (0);
	size = __str_len(str, 0);
	i = 0;
	while (str[i] && str[i] == ' ')
		++i;
	while (str[size - 1] == ' ')
		size--;
	return (size - i);
}

char	*__str_trim(const char *str)
{
	int		size;
	char	*res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	size = check_size(str);
	res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	res[size] = 0;
	i = 0;
	j = -1;
	while (str[i] && str[i] == ' ')
		++i;
	while (++j < size)
		res[j] = str[i + j];
	return (res);
}
