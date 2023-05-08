/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:56:59 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniRT.h"

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
