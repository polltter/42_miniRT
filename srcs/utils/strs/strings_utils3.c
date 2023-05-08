/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:40:01 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:40:08 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/ft_strings.h"

int	__str_len(const char *str, char c);

int	__ends_with(char *src, char *end)
{
	int	len_src;
	int	len_find;

	len_src = s().len(src, 0);
	len_find = s().len(end, 0);
	if (len_src < len_find)
		return (0);
	while (len_src-- && len_find--)
		if (src[len_src] != end[len_find])
			return (0);
	return (1);
}
