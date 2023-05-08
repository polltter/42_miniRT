/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:28:19 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:28:42 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	join_for_each(t_elems *elem, void *o)
{
	(void)o;
	pthread_join(((t_threads *)(elem->cont))->id, NULL);
}

void	delete_images(t_elems *elem, void *o)
{
	(void)o;
	mlx_destroy_image(mlx()->mlx, ((t_threads *)(elem->cont))->img.img);
}
