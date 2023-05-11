/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_reflection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:04:36 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 19:06:02 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
2 * N * dot(N, R) - R
*/
t_coord	reflect_ray(t_coord light, t_coord normal)
{
	return (do_op_coords(SUBTRACT, \
		coord_constant_op(MULTIPLY, normal, \
		dot_product(normal, light) * 2), light));
}

double	to_reflect(t_coord light, t_coord n, t_coord vect, t_coord *reflected)
{
	double	r_dot_v;

	*reflected = reflect_ray(light, n);
	r_dot_v = dot_product(*reflected, vect);
	return (r_dot_v);
}

double	compute_refl(t_coord data, t_coord reflected, t_coord vect)
{
	double	bright;

	bright = (data.x * \
			pow(data.y / (vector_length(reflected) * vector_length(vect)), \
			data.z));
	return (bright);
}
