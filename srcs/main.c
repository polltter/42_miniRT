/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:04:26 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:05:24 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniRT.h"

int	main(int ac, char **av)
{
	t_mlx_data	data;

	build_scene(av[ac - 1]);
	data_init(&data);
	*mlx() = data;
	*first() = array(m()->bodys)->begin;
	*first_l() = array(m()->lights)->begin;
	print_info();
	if (N_THREADS == 1)
		render(NULL);
	else if (N_THREADS > 1)
	{
		build_threads();
		(array(m()->threads))->for_each(init_threads, 0);
		(array(m()->threads))->for_each(join_for_each, 0);
		(array(m()->threads))->for_each(imgs_to_canvas, 0);
		mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, \
								mlx()->img.img, 0, 0);
	}
	mlx_mouse_hook(mlx()->mlx_win, select_body, &data);
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data);
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
