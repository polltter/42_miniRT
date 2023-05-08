/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:31:35 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:11:30 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_coord	canvas_to_viewport(double x, double y);
void	print_coords(t_coord coord);

int	handle_mouse(int button, int x, int y, t_mlx_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	return (0);
}

void    **who_movin(void)
{
    static void *who;

    return (&who);
}

t_elems    **which_light(void)
{
    static t_elems *which;

    return (&which);
}

void	*body_to_move(t_coord O, t_coord viewport_pt) {
    double closest_t;
    void *closest;

    closest_t = INT_MAX;
    closest = closest_intersection(O, viewport_pt, 1, INT_MAX, &closest_t);
	((t_body *)closest)->color = get_rgb(220, 220, 220);
    return (closest);
}

void    zoom(int op)
{
    m()->camera->coord = do_op_coords(op, \
                                    m()->camera->coord, \
                                    m()->camera->vector);
}

int	select_body(int button, int x, int y, t_mlx_data *data)
{
    t_coord viewport_pt;

    (void)data;
    // printf("%d\n", button);
    if (button == 1)
    {
        // theta = find_theta();
        viewport_pt = canvas_to_viewport(x - IMG_W / 2, - y + IMG_H / 2);
        rotate_camera(m()->camera->theta, &viewport_pt);
        // printf("antes -- %p\n", *who_movin());
        (*who_movin()) = body_to_move(m()->camera->coord, viewport_pt);
		if (*who_movin())
			printf("selected body\n");
		if (*which_light())
			toggle_select_light();
        // printf("depois -- %p\n", *who_movin());
    }
    else if (button == 3)
	{
		if (*who_movin())
		{
			((t_body *)(*who_movin()))->color = ((t_body *)(*who_movin()))->original_color;
			printf("deselected body\n");
        	(*who_movin()) = NULL;
		}
		if (*which_light())
			toggle_select_light();
	}
    else if (button == 5 || button == 4)
        zoom(96 + button);
    if (N_THREADS == 1)
        render(NULL);
    else if (N_THREADS > 1)
    {
        array(m()->threads)->for_each(init_threads, 0);
        array(m()->threads)->for_each(join_for_each, 0);
        array(m()->threads)->for_each(imgs_to_canvas, 0);
        mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
    }
    return (0);
}