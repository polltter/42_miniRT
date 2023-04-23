/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ligths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:46:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 19:46:55 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_coord	reflect_ray(t_coord light, t_coord normal)
{
	return (do_op_coords(SUBTRACT, coord_constant_op(MULTIPLY, coord_constant_op(MULTIPLY, normal, 2), dot_product(normal, light)), light));
}

double	compute_lighting(t_coord point, t_coord normal, t_coord vector, double specular)
{
	double 	i;
	double	n_dot_l;
	double	r_dot_v;
	double		shadow_t;
	t_sphere	*shadow_sphere;
	t_elems *temp;
	t_coord	light;
	t_coord	reflected;

	i = 0.0;
	temp = *first_l();
	i += m()->ambient.light_ratio;
	while (temp)
	{
		light = do_op_coords(SUBTRACT, (*(t_light *)temp->cont).coord, point);
		//Shadow check
		shadow_t = INT_MAX;
		shadow_sphere = closest_intersection(point, light, .001, INT_MAX, &shadow_t);
		if (shadow_sphere)
		{
			temp = temp->next;
			continue ;
		}
		//Compute diffusion
		n_dot_l = dot_product(normal, light);
		if (n_dot_l > 0)
			i += (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
		//Compute reflection
		if (specular > 0)
		{
			reflected = reflect_ray(light, normal);
			r_dot_v = dot_product(reflected, vector);
			if (r_dot_v > 0)
				i += (*(t_light *)temp->cont).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
		}
		temp = temp->next;
	}
	if (i > 1) // Incorrect, needs to be improved
		i = 1;
	return(i);
}
