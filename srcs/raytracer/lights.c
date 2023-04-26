/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:46:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/26 14:00:47 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_coord	reflect_ray(t_coord light, t_coord normal)
{
    return (do_op_coords(SUBTRACT, \
		coord_constant_op(MULTIPLY, coord_constant_op(MULTIPLY, normal, 2), \
		dot_product(normal, light)), light));
}

void	clamp_combined(t_coord *combined, double max_light)
{
	if (combined->x > 1) // Incorrect, needs to be improved
		combined->x = 1;
	if (combined->y > 1)
		combined->y = 1;
	if (combined->z > 1)
		combined->z = 1;
	(void)max_light;
	// if (max_light > 0.0)
	// 	printf("%f\n", max_light);
	// combined->x /= (max_light + .8);
	// combined->y /= (max_light + .8);
	// combined->z /= (max_light + .8);
}

void	calc_combined(t_coord *combined, int light_color, double brightness)
{
    combined->x += multiply_component(light_color, 16, brightness) / 255;
    combined->y += multiply_component(light_color, 8, brightness) / 255;
    combined->z += multiply_component(light_color, 0, brightness) / 255;
}

void	diffusion(t_coord *combined, t_coord normal, t_coord light, t_light src)
{
    double		n_dot_l;
    double		bright;

    n_dot_l = dot_product(normal, light);
    if (n_dot_l > 0)
    {
        bright = src.light_ratio * n_dot_l / \
			(vector_length(normal) * vector_length(light));
        calc_combined(combined, src.color, bright);
    }
}

t_coord	compute_lighting(t_coord point, t_coord normal, t_coord vector, double specular)
{
	t_coord 	combined;
	double		r_dot_v;
	t_elems 	*temp;
	t_coord		light;
	t_coord		reflected;
	double		bright;
	double		max_bright;

	combined = set_coord_values(0, 0, 0);
	temp = *first_l();
	max_bright = 0;
	calc_combined(&combined, m()->ambient.color, m()->ambient.light_ratio);
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
		diffusion(&combined, normal, light, *(t_light *)temp->cont);
		//Compute reflection - need to make it into self-contained function
		if (specular > 0)
		{
			reflected = reflect_ray(light, normal);
			r_dot_v = dot_product(reflected, vector);
			if (r_dot_v > 0)
			{
				bright = (*((t_light *)temp->cont)).light_ratio * pow(r_dot_v / (vector_length(reflected) * vector_length(vector)), specular);
				if (bright > max_bright)
					max_bright = bright;
				calc_combined(&combined, (*(t_light *)temp->cont).color, bright);
			}
		}
		temp = temp->next;
	}
	clamp_combined(&combined, max_bright);
	return (combined);
}
