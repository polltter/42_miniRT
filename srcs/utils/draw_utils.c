/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:54:15 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/19 11:44:40 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

double	convert_point(double x, double is_Y)
{
	if (!is_Y)
		return (IMG_W / 2 + x);
	else
		return (IMG_H / 2 - x);
}

