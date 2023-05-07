/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:44:31 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/02 14:34:52 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_point sphere_collision(t_coord O, t_coord viewport_pt, t_sphere sphere)
{
	double	r;
	t_coord	CO;
	t_point	new;

	r = sphere.diameter / 2;
	CO = do_op_coords(SUBTRACT, O, sphere.coord);
	double a = dot_product(viewport_pt, viewport_pt);
	double b = 2 * dot_product(CO, viewport_pt);
	double c = dot_product(CO, CO) - pow(r, 2);
	double discriminant = (b * b) - (4*a*c);
	if (discriminant < 0)
		return ((t_point){INT_MAX, INT_MAX});
	new.x = (-b + sqrt(discriminant)) / (2 * a);
	new.y = (-b - sqrt(discriminant)) / (2 * a);
	return (new);
}

void normalize(t_coord *v)
{
    double len;

    len = vector_length(*v);
    v->x /= len;
    v->y /= len;
    v->z /= len;
}

t_point plane_collision(t_coord viewport_pt, t_plane *plane, t_coord origin)
{
    double  numerator;
    t_point t;

    numerator = 0;
    numerator += plane->vector.x * (origin.x - plane->coord.x);
    numerator += plane->vector.y * (origin.y - plane->coord.y);
    numerator += plane->vector.z * (origin.z - plane->coord.z);
    numerator *= -1;
    t.x = numerator / (viewport_pt.x * plane->vector.x +\
                        viewport_pt.y * plane->vector.y +\
                        viewport_pt.z * plane->vector.z);
    t.y = 0;
    return (t);
}


t_point	collision(t_coord O, t_coord viewport_pt, t_body *body)
{
    if (body->id == SPH)
		return (sphere_collision(O, viewport_pt, *((t_sphere*)body)));
    else if (body->id == PL)
        return (plane_collision(viewport_pt, ((t_plane *)body), O));
    else if (body->id == CY)
        return (cylinder_collision(O, viewport_pt, (t_cylinder *)body));
    return ((t_point){INT_MAX, INT_MAX});
}
