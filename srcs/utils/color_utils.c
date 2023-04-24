/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:34:45 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/24 16:01:49 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

double	multiply_component(int color, int shift, double brightness)
{
	return ((color >> shift & 255) * brightness);
}

int	multiply_color(int color, double brightness)
{
	return (get_rgb(multiply_component(color, 16, brightness), \
			multiply_component(color, 8, brightness), \
			multiply_component(color, 0, brightness)));
}

int	get_color_light(int color, t_coord li)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16 & 255)) * li.x;
	g = ((color >> 8 & 255)) * li.y;
	b = ((color >> 0 & 255)) * li.z;
	return (get_rgb(r, g, b));
}

int	store_colors(int color, int flag)
{
	static int	r;
	static int	g;
	static int	b;
	static int	counter;
	int			c;

	if (!flag)
	{
		r += color >> 16 & 255;
		g += color >> 8 & 255;
		b += color >> 0 & 255;
		counter++;
	}
	else
	{
		c = get_rgb(r / counter, g / counter, b / counter);
		r = 0;
		g = 0;
		b = 0;
		counter = 0;
		return (c);
	}
	return (0);
}
