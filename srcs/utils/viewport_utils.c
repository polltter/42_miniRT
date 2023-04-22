/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:54:15 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 19:29:24 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

double	vp_to_canvas(double x, double is_Y)
{
	if (!is_Y)
		return (IMG_W / 2 + x);
	else
		return (IMG_H / 2 - x);
}

t_coord	canvas_to_viewport(double x, double y)
{
	static t_coord	new;

	new.x = x / IMG_W * m()->viewport.width;
	new.y = y / IMG_H * m()->viewport.height;
	new.z = 1;
	return (new);
}