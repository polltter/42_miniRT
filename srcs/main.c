/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/17 20:35:55 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	render(t_mlx_data *data)
{
	(void)data;
	//draw background
	return (0);
}

int	main(void)
{
	t_mlx_data	data;

	data_init(&data);
	*mlx() = data;
	// mlx_hook(data.mlx_win, 17, 0, ft_close, &data);
	// mlx_hook(mlx()->mlx_win, 2, 1l << 0, handle_keys, NULL);
	
	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
	mlx_loop_hook(mlx()->mlx, render, &data); //hook that is triggered when there's no event processed
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data); //Mais facil de ler
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data); //Mais facil de ler
	mlx_loop(data.mlx);
	return (0);
}
