/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:22:32 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 17:23:31 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_caps(t_cylinder *cy, t_coord normal)
{
	normalize(&normal);
	cy->top.vector = cy->vector;
	cy->bottom.vector = cy->vector;
	cy->top.coord = do_op_coords(ADD, cy->coord, \
					coord_constant_op(MULTIPLY, normal, cy->height / 2));
	cy->bottom.coord = do_op_coords(SUBTRACT, cy->coord, \
					coord_constant_op(MULTIPLY, normal, cy->height / 2));
}

double	collision_plane(t_coord origin, t_coord ray, t_cylinder *body)
{
	t_point	top;
	t_point	bottom;
	t_coord	r_top;
	t_coord	r_bottom;

	update_caps(body, body->vector);
	top = plane_collision(ray, &body->top, origin);
	bottom = plane_collision(ray, &body->bottom, origin);
	r_top = do_op_coords(ADD, origin, coord_constant_op(MULTIPLY, ray, top.x));
	r_top = do_op_coords(SUBTRACT, body->top.coord, r_top);
	r_bottom = do_op_coords(ADD, origin, \
				coord_constant_op(MULTIPLY, ray, bottom.x));
	r_bottom = do_op_coords(SUBTRACT, body->bottom.coord, r_bottom);
	top.y = vector_length(r_top);
	bottom.y = vector_length(r_bottom);
	if (fabs(top.x) > INT_MAX || fabs(bottom.x) > INT_MAX)
		return (INT_MAX);
	top.x += (INT_MAX + fabs(top.x) + 1) * (top.y > body->diameter / 2);
	bottom.x += (INT_MAX + fabs(bottom.x) + 1) * \
				(bottom.y > body->diameter / 2);
	return (top.x * (top.x < bottom.x) + bottom.x * (bottom.x < top.x));
}
