/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:17:15 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 20:17:58 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/miniRT.h"

/* Need to check multiplication and division */
t_coord	do_op_coords(int op, t_coord a, t_coord b)
{
	t_coord	new;

	new.x = do_op(op, a.x, b.x);
	new.y = do_op(op, a.y, b.y);
	new.z = do_op(op, a.z, b.z);
	return (new);
}

t_coord	coord_constant_op(int op, t_coord coord, double constant)
{
	if (op == MULTIPLY)
	{
		coord.x *= constant;
		coord.y *= constant;
		coord.z *= constant;
	}
	else
	{
		coord.x /= constant;
		coord.y /= constant;
		coord.z /= constant;
	}
	return (coord);
}
