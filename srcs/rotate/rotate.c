/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:40:31 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 16:49:08 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void	rotate_x(double theta, t_coord *viewport_pt)
{
	double	temp;

	temp = viewport_pt->y;
	viewport_pt->y = viewport_pt->y * cos(theta) + viewport_pt->z * sin(theta);
	viewport_pt->z = -temp * sin(theta) + viewport_pt->z * cos(theta);
}

void	rotate_y(double theta, t_coord *viewport_pt)
{
	double	temp;

	temp = viewport_pt->x;
	viewport_pt->x = viewport_pt->x * cos(theta) + viewport_pt->z * sin(theta);
	viewport_pt->z = -temp * sin(theta) + viewport_pt->z * cos(theta);
}

void	rotate_z(double theta, t_coord *viewport_pt)
{
	double	temp;

	temp = viewport_pt->x;
	viewport_pt->x = viewport_pt->x * cos(theta) - viewport_pt->y * sin(theta);
	viewport_pt->y = temp * sin(theta) + viewport_pt->y * cos(theta);
}

void	rotate_camera(t_coord theta, t_coord *viewport_pt)
{
	rotate_x(theta.x, viewport_pt);
	rotate_y(theta.y, viewport_pt);
}

void	rotate_plane(int k)
{
	t_plane	*plane;

	plane = (t_plane *)(*who_movin());
	if (k == XK_b)
		rotate_x(0.2, &plane->vector);
	else if (k == XK_h)
		rotate_x(-0.2, &plane->vector);
	else if (k == XK_n)
		rotate_y(0.2, &plane->vector);
	else if (k == XK_j)
		rotate_y(-0.2, &plane->vector);
	else if (k == XK_m)
		rotate_z(0.02, &plane->vector);
	else if (k == XK_k)
		rotate_z(-0.02, &plane->vector);
}
