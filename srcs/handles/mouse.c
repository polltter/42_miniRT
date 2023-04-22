/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:31:35 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/18 16:21:05 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_sphere	*closest_intersection(t_coord O, t_coord D, double t_min, double t_max, double *closest_t);
t_coord	canvas_to_viewport(double x, double y);
void	print_coords(t_coord coord);

int	handle_mouse(int button, int x, int y, t_mlx_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	return (0);
}

void    **who_movin(void)
{
    static void *who;

    return (&who);
}

void	*body_to_move(t_coord O, t_coord D) {
    double closest_t;
    void *closest;

    closest_t = INT_MAX;
    closest = closest_intersection(O, D, 0.00001, INT_MAX, &closest_t);
    return (closest);
}

int	select_body(int button, int x, int y, t_mlx_data *data)
{

    t_coord O = (t_coord){0,0,0};
    t_coord D;


    (void)button;
    (void)x;
    (void)y;
    (void)data;
    if (button == 1)
    {
        D = canvas_to_viewport(x - IMG_W / 2, - y + IMG_H / 2);
        print_coords(D);
        printf("antes -- %p\n", *who_movin());
        (*who_movin()) = body_to_move(O, D);
        printf("depois -- %p\n", *who_movin());
    }
    return (0);
}