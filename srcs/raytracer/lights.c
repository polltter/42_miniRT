/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:46:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 14:11:37 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_coord	clamp_combined(t_coord combined)
{
	if (combined.x > 1)
		combined.x = 1;
	if (combined.y > 1)
		combined.y = 1;
	if (combined.z > 1)
		combined.z = 1;
	return (combined);
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

int	advance_temp(t_elems **temp)
{
	*temp = (*temp)->next;
	return (1);
}

t_coord	compute_lighting(t_coord point, t_coord n, t_coord vect, double spec)
{
	t_coord		combined;
	double		r_dot_v;
	t_elems		*temp;
	t_coord		light;
	t_coord		reflected;

	combined = set_coord_values(0, 0, 0);
	temp = *first_l();
	calc_combined(&combined, m()->ambient->color, m()->ambient->light_ratio);
	while (temp)
	{
		light = do_op_coords(SUBTRACT, (*(t_light *)temp->cont).coord, point);
		if (in_shadow(point, light, .001, 1) && advance_temp(&temp))
			continue ;
		diffusion(&combined, n, light, *(t_light *)temp->cont);
		r_dot_v = to_reflect(light, n, vect, &reflected);
		if (spec > 0 && r_dot_v > 0)
			calc_combined(&combined, (*(t_light *)temp->cont).color, \
			compute_refl((t_coord){(*((t_light *)temp->cont)).light_ratio, \
			r_dot_v, spec}, reflected, vect));
		temp = temp->next;
	}
	return (clamp_combined(combined));
}
