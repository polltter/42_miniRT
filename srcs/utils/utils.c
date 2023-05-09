/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:03:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:03:27 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_main	*m(void)
{
	static t_main	data;

	return (&data);
}

t_coord	set_coord_values(double x, double y, double z)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

void	print_coords(t_coord coord)
{
	printf("%f %f %f\n", coord.x, coord.y, coord.z);
}

t_elems	**first(void)
{
	static t_elems	*a;

	return (&a);
}

t_elems	**first_l(void)
{
	static t_elems	*a;

	return (&a);
}
