/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:43:23 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/24 16:03:37 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_sphere	*closest_intersection(t_coord O, t_coord viewport_pt, double t_min, double t_max, double *closest_t)
{
	t_elems		*temp;
	t_point		t;
	t_sphere	*closest;

	temp = *first();
	closest = NULL;
	while (temp)
	{
		t = collision(O, viewport_pt, (t_default_body *)temp->cont);
		if (t.x > t_min && t.x < t_max && t.x < *closest_t)
		{
			*closest_t = t.x;
			closest = (t_sphere *)(temp->cont);
		}
		if (t.y > t_min && t.y < t_max && t.y < *closest_t)
		{
			*closest_t = t.y;
			closest = (t_sphere *)(temp->cont);
		}
		temp = temp->next;
	}
	return (closest);
}

int	in_shadow(t_coord O, t_coord viewport_pt, double t_min, double t_max)
{
	t_elems		*temp;
	t_point		t;

	temp = *first();
	while (temp)
	{
		t = collision(O, viewport_pt, (t_default_body *)temp->cont);
		if (t.x > t_min && t.x < t_max)
			return (1);
		if (t.y > t_min && t.y < t_max)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	trace_ray(t_coord O, t_coord viewport_pt, double t_min, double t_max, int recursion_depth)
{
	double		closest_t;
	t_sphere	*closest;
	double		reflective;
	int			local_color;
	int			reflected_color;
	t_coord		mirror;

	closest_t = INT_MAX;
	closest = closest_intersection(O, viewport_pt, t_min, t_max, &closest_t);
	if (!closest)
		// return (multiply_color(m()->ambient.color, m()->ambient.light_ratio));
		return (m()->ambient.color);

	t_coord	point = do_op_coords(ADD, O, coord_constant_op(MULTIPLY, viewport_pt, closest_t));
	t_coord normal = do_op_coords(SUBTRACT, point, closest->coord);
	normal = coord_constant_op(DIVIDE, normal, vector_length(normal));
	local_color = get_color_light(closest->color, compute_lighting(point, normal, coord_constant_op(MULTIPLY, viewport_pt, -1), closest->specular));

	reflective = closest->reflective;
	if (recursion_depth <= 0 || reflective <= 0)
		return (local_color);
	mirror = reflect_ray(coord_constant_op(MULTIPLY, viewport_pt, -1), normal);
	reflected_color = trace_ray(point, mirror, .001, INT_MAX, recursion_depth - 1);
	return (get_color_light(local_color, set_coord_values(1 - reflective, 1 - reflective, 1 - reflective)) + get_color_light(reflected_color, set_coord_values(reflective, reflective, reflective)));
	// return (local_color * (1 - reflective) + reflected_color * reflective);
}
