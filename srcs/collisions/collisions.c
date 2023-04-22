/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:44:31 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 20:15:30 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_point	collision(t_coord O, t_coord viewport_pt, t_default_body *body)
{
	if (body->id == SPH)
		return (sphere_collision(O, viewport_pt, *((t_sphere*)body)));
	return ((t_point){INT_MAX, INT_MAX});
}
