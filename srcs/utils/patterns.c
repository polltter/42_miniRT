/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:28:21 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/04 20:33:43 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	stripe_at(t_coord point, t_pattern pattern)
{
	double	mod;

	mod = fmod(point.x, 2.0);
	if ((mod >= 0 && mod < 1) || (mod < -1 && mod > -2))
		return pattern.a;
	return pattern.b;
}

int	square_at(t_coord point, t_pattern pattern)
{
	t_coord new;
	new.x = vp_to_canvas(point.x, 0);
	new.y = vp_to_canvas(point.y, 1);
	new.z = vp_to_canvas(point.z, 0);
	double mod;
	mod = fmod((floor(new.x) + floor(new.y) + floor(new.z)), 2.0);
	if ((mod >= 0.0 && mod < 1.0) /* || (mod < -1 && mod > -2) */)
		return pattern.a;
	return pattern.b;
}