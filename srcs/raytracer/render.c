/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:31:25 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 19:31:44 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

int	render(t_mlx_data *data)
{
	double		x;
	double		y;
	t_coord		viewport_pt;
	t_point		theta;
	int			color;

	(void)data;
	theta = find_theta();
	x = -IMG_W / 2;
	y = -IMG_H / 2;
	while (x < IMG_W / 2)
	{
		while (y < IMG_H / 2)
		{
			viewport_pt = canvas_to_viewport(x, y);
			rotate_camera(theta, &viewport_pt);
			color = trace_ray(m()->camera->coord, viewport_pt, 1, INT_MAX, 3);
			if (vp_to_canvas(x, 0) >= 0 && vp_to_canvas(x, 0) < IMG_W && \
				vp_to_canvas(y, 1) >= 0 && vp_to_canvas(y, 1) < IMG_H)
				my_pixel_put(&mlx()->img, vp_to_canvas(x, 0), \
					vp_to_canvas(y, 1), color);
			y += 1.0;
		}
		y = -IMG_H / 2;
		x += 1.0;
	}
	mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
	return (0);
}