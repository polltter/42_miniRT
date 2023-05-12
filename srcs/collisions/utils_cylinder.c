/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:20:31 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 15:15:11 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	find_distance_in_axis(double t, t_cylinder *cy, t_coord ray, t_coord origin)
{
	t_coord	cross;
	t_coord	center_to_coord;
	double	angle;

	cross = do_op_coords(ADD, \
						origin, \
						coord_constant_op(MULTIPLY, ray, t));
	center_to_coord = do_op_coords(SUBTRACT, cross, cy->coord);
	angle = dot_product(center_to_coord, cy->vector);
	angle = acos(angle / \
			(vector_length(center_to_coord) * vector_length(cy->vector)));
	return ((vector_length(center_to_coord) * cos(angle)));
}

int	in_cylinder(double t, t_cylinder *cy, t_coord ray, t_coord origin)
{
	return (fabs(find_distance_in_axis(t, cy, ray, origin)) > (cy->height / 2));
}

int	in_plane(t_coord point, t_cylinder *cy)
{
	if (fabs(dot_product(cy->vector, \
			do_op_coords(SUBTRACT, cy->top.coord, point)) - 0) < 0.001 || \
		fabs(dot_product(cy->vector, \
			do_op_coords(SUBTRACT, cy->bottom.coord, point)) - 0) < 0.001)
		return (1);
	return (0);
}

t_coord	find_normal(double t, t_cylinder *cy, t_coord ray, t_coord origin)
{
	t_coord	normal;
	t_coord	point_in_axis;
	t_coord	point_in_surface;
	double	dist;

	point_in_surface = do_op_coords(ADD, m()->camera->coord, \
						coord_constant_op(MULTIPLY, ray, t));
	if (in_plane(point_in_surface, cy))
		return (cy->vector);
	dist = find_distance_in_axis(t, cy, ray, origin) / vector_length(cy->vector);
	point_in_axis = coord_constant_op(MULTIPLY, cy->vector, dist);
	point_in_axis = do_op_coords(ADD, cy->coord, point_in_axis);
	normal = do_op_coords(SUBTRACT, point_in_surface, point_in_axis);
	return (normal);
}
