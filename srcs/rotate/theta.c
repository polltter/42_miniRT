/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:42:05 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 16:53:52 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	dot(double v1, double v2, double t1, double t2)
{
	return (v1 * t1 + v2 * t2);
}

double	len2(t_point vector)
{
	return (sqrt((pow(vector.x, 2) + pow(vector.y, 2))));
}

double	find_theta_x(t_coord original, t_coord new_vector)
{
	double	x;

	x = dot(original.y, original.z, new_vector.y, new_vector.z);
	if (!len2((t_point){new_vector.y, new_vector.z}) || \
		!len2((t_point){original.y, original.z}))
		x = 0;
	else if (x > 0)
		x = acos(x / len2((t_point){new_vector.y, new_vector.z}));
	else
		x = M_PI - acos(x / len2((t_point){new_vector.y, new_vector.z}));
	if (new_vector.y < 0)
		x *= -1;
	return (x);
}

double	find_theta_y(t_coord original, t_coord new_vector)
{
	double	y;

	y = dot(original.x, original.z, new_vector.x, new_vector.z);
	if (!len2((t_point){new_vector.x, new_vector.z}) || \
		!len2((t_point){original.x, original.z}))
		y = 0;
	else
		y = acos(y / len2((t_point){new_vector.x, new_vector.z}));
	if (new_vector.x < 0)
		y *= -1;
	return (y);
}

t_coord	find_theta(t_coord original, t_coord new_vector)
{
	t_coord	theta;

	theta.x = find_theta_x(original, new_vector);
	theta.y = find_theta_y(original, new_vector);
	theta.z = dot(original.x, original.y, new_vector.x, new_vector.y);
	if (!len2((t_point){new_vector.x, new_vector.y}) || \
		!len2((t_point){original.x, original.y}))
		theta.z = 0;
	else if (theta.z > 0)
		theta.z = acos(theta.z / len2((t_point){new_vector.x, new_vector.y}));
	else
		theta.z = -M_PI + \
				acos(theta.z / len2((t_point){new_vector.x, new_vector.y}));
	return (theta);
}
