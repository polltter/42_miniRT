/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:57:55 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/19 15:57:25 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

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

double	vector_length(t_coord vector)
{
	double	len;

	len = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (len);
}
