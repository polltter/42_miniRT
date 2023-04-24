/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:46:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/24 15:24:14 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_coord	reflect_ray(t_coord light, t_coord normal)
{
	return (do_op_coords(SUBTRACT, coord_constant_op(MULTIPLY, coord_constant_op(MULTIPLY, normal, 2), dot_product(normal, light)), light));
}

t_coord calc_colors_combined(t_coord combined, int light_color, double brightness)
{
	combined.x = (light_color >> 16 & 255) * brightness / 255;
	combined.y = (light_color >> 8 & 255) * brightness / 255;
	combined.z = (light_color >> 0 & 255) * brightness / 255;

	return (combined);
}

t_coord	compute_lighting(t_coord point, t_coord normal, t_coord vector, double specular)
{
	t_coord 	combined;
	double		n_dot_l;
	double		r_dot_v;
	t_elems 	*temp;
	t_coord		light;
	t_coord		reflected;
	// double		bright;

	combined = set_coord_values(0, 0, 0);
	temp = *first_l();
	// calc_colors_combined(combined, m()->ambient.color, m()->ambient.light_ratio);
	combined.x = (m()->ambient.color >> 16 & 255) / 255 * m()->ambient.light_ratio;
	combined.y = (m()->ambient.color >> 8 & 255) / 255 * m()->ambient.light_ratio;
	combined.z = (m()->ambient.color >> 0 & 255) / 255 * m()->ambient.light_ratio;
	while (temp)
	{
		light = do_op_coords(SUBTRACT, (*(t_light *)temp->cont).coord, point);
		//Shadow check
		if (in_shadow(point, light, .001, INT_MAX))
		{
			temp = temp->next;
			continue ;
		}
		//Compute diffusion
		n_dot_l = dot_product(normal, light);
		if (n_dot_l > 0)
		{
			// bright = (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
			// calc_colors_combined(combined, (*(t_light *)temp->cont).color, bright);
			combined.x += ((*(t_light *)temp->cont).color >> 16 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
			combined.y += ((*(t_light *)temp->cont).color >> 8 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
			combined.z += ((*(t_light *)temp->cont).color >> 0 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
		}
		//Compute reflection
		if (specular > 0)
		{
			reflected = reflect_ray(light, normal);
			r_dot_v = dot_product(reflected, vector);
			if (r_dot_v > 0)
			{
				// bright = (*((t_light *)temp->cont)).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
				// calc_colors_combined(combined, (*(t_light *)temp->cont).color, bright);
				combined.x += ((*(t_light *)temp->cont).color >> 16 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
				combined.y += ((*(t_light *)temp->cont).color >> 8 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
				combined.z += ((*(t_light *)temp->cont).color >> 0 & 255) / 255 * (*(t_light *)temp->cont).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
			}
		}
		temp = temp->next;
	}
	if (combined.x > 1) // Incorrect, needs to be improved
		combined.x = 1;
	if (combined.y > 1)
		combined.y = 1;
	if (combined.z > 1)
		combined.z = 1;
	return (combined);
}
