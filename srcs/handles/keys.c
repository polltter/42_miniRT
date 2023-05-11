/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:37:56 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 17:52:16 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

int	move_body(int k)
{
	if (k == XK_a)
		((t_body *)(*who_movin()))->coord.x -= 0.1;
	else if (k == XK_d)
		((t_body *)(*who_movin()))->coord.x += 0.1;
	else if (k == XK_w)
		((t_body *)(*who_movin()))->coord.y += 0.1;
	else if (k == XK_s)
		((t_body *)(*who_movin()))->coord.y -= 0.1;
	else if ((((t_body *)(*who_movin()))->id == PL || \
			((t_body *)(*who_movin()))->id == CY) && \
		(k == XK_b || k == XK_h || k == XK_n || k == XK_j || \
		k == XK_m || k == XK_k))
		rotate_plane(k);
	else if (k == XK_Up)
		((t_body *)(*who_movin()))->coord.z += 0.1;
	else if (k == XK_Down)
		((t_body *)(*who_movin()))->coord.z -= 0.1;
	else if (k == XK_r)
		((t_sphere *)(*who_movin()))->diameter *= 1.1;
	else if (k == XK_t)
		((t_sphere *)(*who_movin()))->diameter /= 1.1;
	else
		return (0);
	return (1);
}

int	move_camera(int k)
{
	if (k == XK_a)
		m()->camera->coord.x -= 0.1;
	else if (k == XK_d)
		m()->camera->coord.x += 0.1;
	else if (k == XK_w)
		m()->camera->coord.y += 0.1;
	else if (k == XK_s)
		m()->camera->coord.y -= 0.1;
	else if (k == XK_Up)
	{
		rotate_x(0.2, &m()->camera->vector);
		m()->camera->theta.x += 0.2;
	}
	else if (k == XK_Down)
	{
		rotate_x(-0.2, &m()->camera->vector);
		m()->camera->theta.x -= 0.2;
	}
	else if (k == XK_Left)
	{
		rotate_y(-0.2, &m()->camera->vector);
		m()->camera->theta.y -= 0.2;
	}
	else if (k == XK_Right)
	{
		rotate_y(0.2, &m()->camera->vector);
		m()->camera->theta.y += 0.2;
	}
	else if (!(*who_movin()) && !(*which_light()) && (k == XK_minus || k == 65453) && m()->ambient->light_ratio > .1)
		m()->ambient->light_ratio -= .1;
	else if (!(*who_movin()) && !(*which_light()) && (k == XK_plus || k == 65451) && m()->ambient->light_ratio < .9)
		m()->ambient->light_ratio += .1;
	else
		return (0);
	return (1);
}

int	handle_keys(int k)
{
	int	to_render;

	to_render = 0;
	if (k == XK_Escape)
		ft_close(mlx());
	if (k == XK_l && toggle_select_light())
		to_render = 1;
	if ((*who_movin()) && !move_body(k))
		return (0);
	if ((*which_light()) && !to_render && !move_light(k))
		return (0);
	if ((!*who_movin() && !*which_light()) && !move_camera(k))
		return (0);
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
	return (1);
}
