/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:28:21 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/05 16:22:29 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	stripe_at(t_coord point, t_pattern pattern)
{
	double	mod;

	mod = fmod(point.x, 2.0);
	if ((mod >= 0 && mod < 1) || (mod < -1 && mod > -2))
		return pattern.a;
	return pattern.b;
}

// int	square_at(t_coord point, t_pattern pattern)
// {
	// double	scaling = 4;
	// t_coord new;
	// new.x = vp_to_canvas(point.x, 0) * scaling;
	// new.y = vp_to_canvas(point.y, 1) * scaling;
	// new.z = vp_to_canvas(point.z, 0) * scaling;
	// double mod;
	// mod = fmod((floor(new.x) + floor(new.y) + floor(new.z)), 2.0);
	// mod = fmod(((new.x - floor(new.x)) + (new.y - floor(new.y)) + (new.z - floor(new.z))), 2.0);
// 	if ((mod >= 0.0 && mod < 1.0) /* || (mod < -1 && mod > -2) */)
// 		return pattern.a;
// 	return pattern.b;
// }

t_coord	cross_product(t_coord a, t_coord b)
{
	t_coord cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = -(a.x * b.z - a.z * b.x);
	cross.z = a.x * b.y - b.x * a.y;

	return (cross);
}

int	square_at(t_coord normal, t_coord point, t_pattern pattern)
{
	double scaling = .5;
	t_coord u = {normal.y, -normal.x, 0};
	/* if (normal.x == 0)
		u.y = -normal.z;
	else if (normal.y  == 0)
		u.x = normal.z; */
	if (u.x == 0 && u.y == 0)
		u.x = normal.z;
	u = coord_constant_op(DIVIDE, u, vector_length(u));

	t_coord v = cross_product(normal, u);
	coord_constant_op(DIVIDE, v, vector_length(v));

	double u_coord = dot_product(u, point) * scaling;
	double v_coord = dot_product(v, point) * scaling;
	
	double mod;
	mod = fmod((floor(u_coord) + floor(v_coord)), 2.0);
	if (!mod)
		return pattern.a;
	return pattern.b;
}