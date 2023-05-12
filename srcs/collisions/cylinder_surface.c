/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_surface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:21:59 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 15:46:10 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	surface_calc(t_coord ray, t_cylinder *body, \
				t_coord t, t_coord origin)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqr_mod;

	sqr_mod = pow(vector_length((body)->vector), 2);
	a = dot_product(ray, ray) \
		* sqr_mod \
		- pow(dot_product(ray, (body)->vector), 2);
	b = 2 * dot_product(t, ray) * sqr_mod \
			- 2 * dot_product(ray, body->vector) * dot_product(t, body->vector);
	c = (dot_product(t, t) - pow((body)->diameter / 2, 2)) * sqr_mod \
		- pow(dot_product(t, (body)->vector), 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (INT_MAX);
	c = (-b + sqrt(discriminant)) / (2 * a);
	a = (-b - sqrt(discriminant)) / (2 * a);
	c += in_cylinder(c, (t_cylinder *)body, ray, origin) * \
					(INT_MAX + fabs(c) + 1);
	a += in_cylinder(a, (t_cylinder *)body, ray, origin) * \
					(INT_MAX + fabs(a) + 1);
	return (c * (c < a) + a * (a < c));
}

double	collision_cy_surface(t_coord origin, t_coord ray, t_cylinder *body)
{
	t_coord	to_center;

	to_center = do_op_coords(SUBTRACT, origin, (body)->coord);
	return (surface_calc(ray, body, to_center, origin));
}
