/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 16:48:08 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniRT.h"

/* Deixo aqui para nao nos esquecermos de apagar */
void	print_coords(t_coord coord)
{
	printf("%f %f %f\n", coord.x, coord.y, coord.z);
}

t_elems **first(void)
{
    static t_elems *a;

    return (&a);
}

t_elems **first_l(void)
{
    static t_elems *a;

    return (&a);
}

void    *render_t(void *t)
{
    t_threads *thread = t;
    double		x;
    double		y;
    t_coord		viewport_pt;
    int			color;

    x = 0;
    while (x < thread->end_x - thread->strat_x)
    {
        y = -IMG_H / 2;
        while (y < IMG_H / 2)
        {
            viewport_pt = canvas_to_viewport(x - 1 + thread->strat_x, y);
            rotate_camera(m()->camera->theta, &viewport_pt);
            color = trace_ray(m()->camera->coord, viewport_pt, 1, INT_MAX, 2);
            if (vp_to_canvas(x, 0) >= 0 && vp_to_canvas(x, 0) < IMG_W && \
				vp_to_canvas(y, 1) >= 0 && vp_to_canvas(y, 1) < IMG_H)
                my_pixel_put(&thread->img, vp_to_canvas(x - IMG_W / 2, 0), \
					vp_to_canvas(y, 1), color);
            y += 1.0;
        }
        x += 1.0;
    }
    return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data_init(&data);
	*mlx() = data;
    build_scene(av[ac - 1]);
//	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
    *first() = array(m()->bodys)->begin;
    *first_l() = array(m()->lights)->begin;
	print_info();
    if (N_THREADS == 1)
        render(NULL);
    else if (N_THREADS > 1)
    {
        build_threads();
//        array(m()->threads)->for_each(print_threads, 0);
        array(m()->threads)->for_each(init_threads, 0);
        array(m()->threads)->for_each(join_for_each, 0);
        array(m()->threads)->for_each(imgs_to_canvas, 0);
        mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
    }
	mlx_mouse_hook(mlx()->mlx_win, select_body, &data);
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data);
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
