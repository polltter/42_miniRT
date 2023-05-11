/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:54:27 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 17:02:24 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_point	collision_point(t_coord viewport_pt, t_coord t, double r, t_point new)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dot_product(viewport_pt, viewport_pt);
	b = 2 * dot_product(t, viewport_pt);
	c = dot_product(t, t) - pow(r, 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return ((t_point){INT_MAX, INT_MAX});
	new.x = (-b + sqrt(discriminant)) / (2 * a);
	new.y = (-b - sqrt(discriminant)) / (2 * a);
	return (new);
}

t_point	sphere_collision(t_coord origin, t_coord viewport_pt, t_sphere sphere)
{
	double	r;
	t_coord	t;
	t_point	new;

	r = sphere.diameter / 2;
	t = do_op_coords(SUBTRACT, origin, sphere.coord);
	new = collision_point(viewport_pt, t, r, new);
	return (new);
}

void	normalize(t_coord *v)
{
	double	len;

	len = vector_length(*v);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

t_point	plane_collision(t_coord viewport_pt, t_plane *plane, t_coord origin)
{
	double	numerator;
	t_point	t;

	numerator = 0;
	numerator += plane->vector.x * (origin.x - plane->coord.x);
	numerator += plane->vector.y * (origin.y - plane->coord.y);
	numerator += plane->vector.z * (origin.z - plane->coord.z);
	numerator *= -1;
	t.x = numerator / (viewport_pt.x * plane->vector.x + \
						viewport_pt.y * plane->vector.y + \
						viewport_pt.z * plane->vector.z);
	t.y = 0;
	return (t);
}

t_point	collision(t_coord origin, t_coord viewport_pt, t_body *body)
{
	if (body->id == SPH)
		return (sphere_collision(origin, viewport_pt, *((t_sphere *)body)));
	else if (body->id == PL)
		return (plane_collision(viewport_pt, ((t_plane *)body), origin));
	else if (body->id == CY)
		return (cylinder_collision(origin, viewport_pt, (t_cylinder *)body));
	return ((t_point){INT_MAX, INT_MAX});
}
