/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:33:05 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/17 20:33:30 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void    **who_movin(void);

int	handle_keys(int k)
{
    if (k == XK_Escape)
		ft_close(mlx());
    else if (k == XK_a && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.x -= 0.1;
    else if (k == XK_d && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.x += 0.1;
    else if (k == XK_w && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.y += 0.1;
    else if (k == XK_s && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.y -= 0.1;
    else if (k == XK_Up && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.z += 0.1;
    else if (k == XK_Down && (*who_movin()))
        ((t_default_body *)(*who_movin()))->coord.z -= 0.1;
    else
        return (0);
    array(m()->threads)->for_each(init_threads, 0);
    array(m()->threads)->for_each(join_for_each, 0);
    array(m()->threads)->for_each(imgs_to_canvas, 0);
    return (1);
}
