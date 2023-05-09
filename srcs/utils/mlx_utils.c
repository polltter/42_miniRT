/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:34:39 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 16:47:40 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_mlx_data	*mlx(void)
{
	static t_mlx_data	data;

	return (&data);
}

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	data_init(t_mlx_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, IMG_W, IMG_H, "MiniRT");
	data->img.img = mlx_new_image(data->mlx, IMG_W, IMG_H);
	data->img.addr = mlx_get_data_addr(data->img.img, \
	&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

int	ft_close(t_mlx_data *data)
{
	if (N_THREADS > 1)
	{
		(array(m()->threads))->for_each(delete_images, 0);
		array(m()->threads)->destroy();
	}
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(m()->ambient);
	free(m()->camera);
	array(m()->lights)->destroy();
	array(m()->bodys)->destroy();
	free(data->mlx);
	exit(0);
}
