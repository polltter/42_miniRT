/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:42:35 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:01:49 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

int	ft_atoi(char *nptr, long int max)
{
	int	sign;
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - '0';
		i++;
		if (nb > max && printf("Max: %ld\nArgument %s too big.\n", max, nptr))
			return (INT_MAX);
	}
	return (sign * nb);
}

double	ft_atod(char *str, double m)
{
	int		i;
	double	d;
	int		sign;
	int		j;

	sign = 1;
	d = 0;
	j = 0;
	i = ft_atoi(str, ceil(m));
	if (i == INT_MAX)
		return (INT_MAX);
	if (!s().contains(str, "."))
		return (i * 1.0);
	if (*str == '-')
		sign = -1;
	while (str[j])
		j++;
	while (j && str[--j] >= '0' && str[j] <= '9')
	{
		d += str[j] - '0';
		d /= 10.0;
	}
	if ((sign * d + i) > m && printf("Max: %f\nArgument %s too big.\n", m, str))
		return (INT_MAX);
	return (sign * d + i);
}

void	freepp(void **to_free)
{
	int	i;

	i = -1;
	while (to_free[++i])
		free(to_free[i]);
	free(to_free);
}

int	arr_size(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	error(char *err)
{
	if (m()->ambient)
		free(m()->ambient);
	if (m()->camera)
		free(m()->camera);
	if (array(m()->lights))
		array(m()->lights)->destroy();
	if (array(m()->bodys))
		array(m()->bodys)->destroy();
	exit(write(2, err, s().len(err, 0)));
}
