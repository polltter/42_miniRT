/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 19:59:16 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniRT.h"

/* Deixo aqui para nao nos esquecermos de apagar */
void	print_coords(t_coord coord)
{
	printf("%f %f %f\n", coord.x, coord.y, coord.z);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data_init(&data);
	*mlx() = data;
    build_scene(av[ac - 1]);
//	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
    render(NULL);
	mlx_mouse_hook(mlx()->mlx_win, select_body, &data);
//	mlx_loop_hook(mlx()->mlx, render, &data);
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data);
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
