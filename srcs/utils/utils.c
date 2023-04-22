/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:57:55 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 20:18:44 by touteiro         ###   ########.fr       */
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




