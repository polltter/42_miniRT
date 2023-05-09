/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:25:25 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 18:56:32 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void	init_threads(t_elems *elem, void *o)
{
	(void)o;
	pthread_create(&(((t_threads *)(elem->cont))->id), NULL, \
					render_t, elem->cont);
}

void	print_threads(t_elems *elem, void *o)
{
	t_threads	*a;

	(void)o;
	a = (t_threads *)elem->cont;
	printf("%d--%d\n", a->start_x, a->end_x);
}

void	imgs_to_canvas(t_elems *elem, void *o)
{
	int			x;
	int			y;
	t_threads	*thread;

	(void)o;
	y = -1;
	thread = ((t_threads *)elem->cont);
	while (++y < IMG_H)
	{
		x = -1;
		while (++x < IMG_W / N_THREADS)
		{
			my_pixel_put(&mlx()->img, thread->start_x + IMG_W / 2 + x, y, \
			my_mlx_pixel_get(&thread->img, x, y));
		}
	}
}

void	build_threads(void)
{
	int			i;
	t_threads	*new;

	i = 0;
	m()->threads = creat_array();
	while (i < N_THREADS)
	{
		new = ft_calloc(sizeof(t_threads));
		new->id = i;
		new->start_x = i * IMG_W / N_THREADS - IMG_W / 2;
		new->end_x = (i + 1) * IMG_W / N_THREADS - IMG_W / 2;
		new->img.img = mlx_new_image(mlx()->mlx, \
						new->end_x - new->start_x, IMG_H);
		new->img.addr = mlx_get_data_addr(new->img.img, \
		&new->img.bits_per_pixel, &new->img.line_length, &new->img.endian);
		array(m()->threads)->add(new);
		i++;
	}
}
