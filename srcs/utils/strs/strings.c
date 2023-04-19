/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:12:25 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:56:03 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char		**ft_split(const char *str, int sep);
int			__str_len(const char *str, char c);
int			__strn_cmp(const char *str1, const char *str2, int n);
int			__strn_str(const char *haystack, const char *needle);
char		*__str_trim(const char *str);
int			__isal_num(char *str);
char		*__append(char *s, char c);

static char	*__strn_dup(const char *str, int size)
{
	char	*ret;
	int		i;

	if (__str_len(str, 0) < size)
		size = __str_len(str, 0);
	ret = ft_calloc(size + 1);
	i = -1;
	while (++i < size)
		ret[i] = str[i];
	return (ret);
}

static char	*__str_dup(const char *str)
{
	int		size;
	char	*ret;

	size = __str_len(str, 0);
	ret = ft_calloc(size + 1);
	while (size--)
		ret[size] = str[size];
	return (ret);
}

int	__str_cmp(const char *str1, const char *str2)
{
	int	i;

	i = -1;
	if (str1 && str2)
		while (str1[++i] || str2[i])
			if (str1[i] != str2[i])
				return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

char	*__str_join(char *s1, char *s2, char *sep)
{
	char	*new;
	int		i;

	new = ft_calloc(__str_len(s1, 0) + __str_len(s2, 0) + __str_len(sep, 0)
			+ 1);
	i = -1;
	while (++i < __str_len(s1, 0))
		new[i] = s1[i];
	i = -1;
	while (++i < __str_len(sep, 0))
		new[__str_len(s1, 0) + i] = sep[i];
	i = -1;
	while (++i < __str_len(s2, 0))
		new[__str_len(s1, 0) + __str_len(sep, 0) + i] = s2[i];
	return (new);
}

t_s	s(void)
{
	static t_s	string = {
		__str_len,
		__str_dup,
		__strn_dup,
		ft_split,
		__str_cmp,
		__strn_cmp,
		__strn_str,
		__str_trim,
		__str_join,
		__isal_num,
		__append,
	};

	return (string);
}
