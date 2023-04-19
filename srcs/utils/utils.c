/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:57:55 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/19 12:15:59 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_main	*m(void)
{
	static t_main	data;

	return (&data);
}

double	do_op(int op, double a, double b)
{
	if (op == ADD)
		return (a + b);
	else if (op == SUBTRACT)
		return (a - b);
	else if (op == MULTIPLY)
		return (a * b);
	else if (op == DIVIDE && b)
		return (a / b);
	return (0);
}

/* Need to check multiplication and division */
t_coord	do_op_coords(int op, t_coord a, t_coord b)
{
	t_coord	new;

	new.x = do_op(op, a.x, b.x);
	new.y = do_op(op, a.y, b.y);
	new.z = do_op(op, a.z, b.z);
	return (new);
}

t_coord	set_coord_values(double x, double y, double z)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}
