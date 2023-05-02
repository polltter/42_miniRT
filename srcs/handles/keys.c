/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:33:05 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/26 17:59:47 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void    **who_movin(void);



int move_body(int k)
{
    if (k == XK_a)
        ((t_default_body *)(*who_movin()))->coord.x -= 0.1;
    else if (k == XK_d)
        ((t_default_body *)(*who_movin()))->coord.x += 0.1;
    else if (k == XK_w)
        ((t_default_body *)(*who_movin()))->coord.y += 0.1;
    else if (k == XK_s)
        ((t_default_body *)(*who_movin()))->coord.y -= 0.1;
    else if (k == XK_Up)
        ((t_default_body *)(*who_movin()))->coord.z += 0.1;
    else if (k == XK_Down)
        ((t_default_body *)(*who_movin()))->coord.z -= 0.1;
    else if (k == XK_r)
        ((t_sphere *)(*who_movin()))->diameter *= 1.1;
    else
        return (0);
    return (1);
}

int move_camera(int k)
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
        m()->camera->vector.y += 0.1;
    else if (k == XK_Down)
        m()->camera->vector.y -= 0.1;
    else if (k == XK_Left)
        m()->camera->vector.x -= 0.1;
    else if (k == XK_Right)
        m()->camera->vector.x += 0.1;
    else
	{
        return (0);
	}
	m()->camera->theta = find_theta((t_coord){0, 0, 1}, m()->camera->vector);
    return (1);
}

int	handle_keys(int k)
{
    if (k == XK_Escape)
		ft_close(mlx());
    if (*who_movin() && !move_body(k))
        return (0);
    else if (!*who_movin() && !move_camera(k))
        return (0);
    if (N_THREADS == 1)
        render(NULL);
    else if (N_THREADS > 1)
    {
        array(m()->threads)->for_each(init_threads, 0);
        array(m()->threads)->for_each(join_for_each, 0);
        array(m()->threads)->for_each(imgs_to_canvas, 0);
        mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
    }
    return (1);
}
