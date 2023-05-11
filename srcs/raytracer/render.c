/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:19:37 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 20:02:18 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void	render(void)
{
	double		x;
	double		y;
	t_coord		vp_pt;
	int			color;

	x = -IMG_W / 2;
	y = -IMG_H / 2;
	while (x < IMG_W / 2)
	{
		while (y < IMG_H / 2)
		{
			vp_pt = canvas_to_viewport(x, y);
			rotate_camera(m()->camera->theta, &vp_pt);
			color = trace_ray(m()->camera->coord, vp_pt, \
							(t_point){1, INT_MAX}, 3);
			my_pixel_put(&mlx()->img, vp_to_canvas(x, 0), \
				vp_to_canvas(y, 1), color);
			y += 1.0;
		}
		y = -IMG_H / 2;
		x += 1.0;
	}
	mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
}

void	*render_t(void *t)
{
	t_threads	*thread;
	double		x;
	double		y;
	t_coord		vp_pt;
	int			color;

	thread = t;
	x = 0;
	while (x < thread->end_x - thread->start_x)
	{
		y = -IMG_H / 2;
		while (y < IMG_H / 2)
		{
			vp_pt = canvas_to_viewport(x - 1 + thread->start_x, y);
			rotate_camera(m()->camera->theta, &vp_pt);
			color = trace_ray(m()->camera->coord, vp_pt, \
							(t_point){1, INT_MAX}, 2);
			my_pixel_put(&thread->img, vp_to_canvas(x - IMG_W / 2, 0), \
				vp_to_canvas(y, 1), color);
			y += 1.0;
		}
		x += 1.0;
	}
	return (0);
}
