/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:43:23 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 15:17:50 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_body	*closest_intersection(t_coord origin, t_coord viewport_pt, \
	t_point limits, double *closest_t)
{
	t_elems		*temp;
	t_point		t;
	t_body		*closest;

	temp = *first();
	closest = NULL;
	while (temp)
	{
		t = collision(origin, viewport_pt, (t_body *)temp->cont);
		if (t.x > limits.x && t.x < limits.y && t.x < *closest_t)
		{
			*closest_t = t.x;
			closest = (t_body *)(temp->cont);
		}
		if (t.y > limits.x && t.y < limits.y && t.y < *closest_t)
		{
			*closest_t = t.y;
			closest = (t_body *)(temp->cont);
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
		t = collision(O, viewport_pt, (t_body *)temp->cont);
		if (t.x > t_min && t.x < t_max)
			return (1);
		if (t.y > t_min && t.y < t_max)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_coord	calc_normal(t_body *closest, t_coord point, double t, t_coord vp_pt)
{
	t_coord	normal;

	if (closest->id == SPH)
	{
		normal = do_op_coords(SUBTRACT, point, closest->coord);
		normal = coord_constant_op(DIVIDE, normal, vector_length(normal));
	}
	else if (closest->id == PL)
		normal = ((t_plane *)closest)->vector;
	else
		normal = find_normal(t, (t_cylinder *)closest, vp_pt, m()->camera->coord);
	if (dot_product(normal, vp_pt) > 0)
		normal = coord_constant_op(MULTIPLY, normal, -1);
	return (normal);
}

t_coord	to_coord(double value)
{
	t_coord	new;

	new.x = value;
	new.y = value;
	new.z = value;
	return (new);
}

int	trace_ray(t_coord origin, t_coord vp_pt, t_point limits, int rec_depth)
{
	double		t;
	t_body		*closest;
	int			local_color;
	t_coord		normal;
	t_coord		point;

	t = INT_MAX;
	closest = closest_intersection(origin, vp_pt, limits, &t);
	if (!closest)
		return (multiply_color(m()->ambient->color, m()->ambient->light_ratio));
	point = do_op_coords(ADD, origin, coord_constant_op(MULTIPLY, vp_pt, t));
	normal = calc_normal(closest, point, t, vp_pt);
	local_color = get_color_light(closest->color, compute_lighting(point, \
		normal, coord_constant_op(MULTIPLY, vp_pt, -1), closest->specular));
	if (rec_depth <= 0 || closest->reflective <= 0)
		return (local_color);
	return (get_color_light(local_color, to_coord(1 - closest->reflective)) + \
		get_color_light(trace_ray(point, \
		reflect_ray(coord_constant_op(MULTIPLY, vp_pt, -1), normal), \
		(t_point){.001, INT_MAX}, rec_depth - 1), \
		to_coord(closest->reflective)));
}
