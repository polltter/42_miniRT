/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:03:41 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 15:23:07 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_point	cylinder_collision(t_coord origin, t_coord ray, t_cylinder *body)
{
	t_point	new;
	double	surface = INT_MAX;
	double	plane = INT_MAX;

	surface = collision_cy_surface(origin, ray, body);
	plane = collision_cy_plane(origin, ray, body);
	new.x = surface * (surface < plane) + plane * (plane < surface);
	new.y = 0;
	return (new);
}
