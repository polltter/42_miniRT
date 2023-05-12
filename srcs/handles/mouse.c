/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:05:34 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 15:36:23 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void	*body_to_move(t_coord origin, t_coord viewport_pt)
{
	double	closest_t;
	void	*closest;

	closest_t = INT_MAX;
	closest = closest_intersection(origin, viewport_pt, \
			(t_point){1, INT_MAX}, &closest_t);
	if (closest)
		((t_body *)closest)->color = get_rgb(220, 220, 220);
	return (closest);
}

void	zoom(int op)
{
	(m())->camera->coord = do_op_coords(op, \
									m()->camera->coord, \
									m()->camera->vector);
}

void	left_click(int x, int y)
{
	t_coord	viewport_pt;

	viewport_pt = canvas_to_viewport(x - IMG_W / 2, -y + IMG_H / 2);
	rotate_camera(m()->camera->theta, &viewport_pt);
	if (*who_movin())
		((t_body *)(*who_movin()))->color = \
			((t_body *)(*who_movin()))->original_color;
	(*who_movin()) = body_to_move(m()->camera->coord, viewport_pt);
	if (*which_light())
		toggle_select_light();
}

void	right_click(void)
{
	if (*who_movin())
	{
		((t_body *)(*who_movin()))->color = \
			((t_body *)(*who_movin()))->original_color;
		(*who_movin()) = NULL;
	}
	if (*which_light())
		toggle_select_light();
}

int	select_body(int button, int x, int y, t_mlx_data *data)
{
	(void)data;
	if (button == 1)
		left_click(x, y);
	else if (button == 3)
		right_click();
	else if (button == 5 || button == 4)
		zoom(96 + button);
	if (N_THREADS == 1)
		render();
	else if (N_THREADS > 1)
	{
		(array(m()->threads))->for_each(init_threads, 0);
		(array(m()->threads))->for_each(join_for_each, 0);
		(array(m()->threads))->for_each(imgs_to_canvas, 0);
		mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, \
								mlx()->img.img, 0, 0);
	}
	return (0);
}
