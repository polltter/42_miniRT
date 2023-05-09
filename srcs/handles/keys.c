/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:33:05 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:29:43 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

int		toggle_select_light(void)
{
	static int	selected;
	
	if (!selected)
	{
		if (*who_movin())
		{
			((t_body *)(*who_movin()))->color = ((t_body *)(*who_movin()))->original_color;
			printf("deselected body\n");
        	(*who_movin()) = NULL;
		}
		printf("selected light 1\n");
		// printf("original light ratio is %f\n", ((t_light *)m()->lights)->light_ratio);
		(*which_light()) = array(m()->lights)->begin;
		(*who_movin()) = NULL;
		selected = 1;
	}
	else
	{
		printf("deselected lights\n");
		(*which_light()) = NULL;
		selected = 0;
	}
	return (selected);
}

int	move_light(int k)
{
	t_light		*temp;
	t_elems		*list;
	int			selected;
	
	selected = 0;
	temp = (*which_light())->cont;
	list = array(m()->lights)->begin;
	/* Transform in indexOf */
	while (list && list->next && temp != list->cont)
	{
		selected++;
		list = list->next;
	}
	if ((k == XK_minus || k == 65453) && temp->light_ratio > .1)
		temp->light_ratio -= .1;
	else if ((k == XK_plus || k == 65451) && temp->light_ratio < 1)
		temp->light_ratio += .1;
	else if (k == XK_Right)
	{
		if ((*which_light())->next)
		{
			(*which_light()) = (*which_light())->next;
			selected++;
			printf("selected light %d\n", selected + 1);
		}
		else
		{
			(*which_light()) = array(m()->lights)->begin;
			selected = 0;
			printf("selected light %d\n", selected + 1);
		}
	}
	else if (k == XK_Left)
	{
		if ((*which_light())->prev)
		{
			(*which_light()) = (*which_light())->prev;
			selected--;
			printf("selected light %d\n", selected + 1);
		}
		else
		{
			(*which_light()) = array(m()->lights)->end;
			selected = array(m()->lights)->size - 1;
			printf("selected light %d\n", selected + 1);
		}
	}
	else if (k == XK_a)
		temp->coord.x -= .1;
	else if (k == XK_d)
		temp->coord.x += .1;
	else if (k == XK_s)
		temp->coord.y -= .1;
	else if (k == XK_w)
		temp->coord.y += .1;
	else if (k == XK_Up)
		temp->coord.z += .1;
	else if (k == XK_Down)
		temp->coord.z -= .1;
	else
		return (0);
	return (1);
}

int move_body(int k)
{
    // printf("%d, X: %d,x: %d\n", k, XK_X, XK_x);
    if (k == XK_a)
        ((t_body *)(*who_movin()))->coord.x -= 0.1;
    else if (k == XK_d)
        ((t_body *)(*who_movin()))->coord.x += 0.1;
    else if (k == XK_w)
        ((t_body *)(*who_movin()))->coord.y += 0.1;
    else if (k == XK_s)
        ((t_body *)(*who_movin()))->coord.y -= 0.1;
	else if (((t_body *)(*who_movin()))->id == PL && \
		(k == XK_b || k == XK_h || k == XK_n || k == XK_j || k == XK_m || k == XK_k))
        rotate_plane(k);
    else if (k == XK_Up)
        ((t_body *)(*who_movin()))->coord.z += 0.1;
    else if (k == XK_Down)
        ((t_body *)(*who_movin()))->coord.z -= 0.1;
    else if (k == XK_r)
        ((t_sphere *)(*who_movin()))->diameter *= 1.1;
	else if (k == XK_t)
        ((t_sphere *)(*who_movin()))->diameter /= 1.1;
    else
        return (0);
    return (1);
}

int move_camera(int k)
{
    if (k == XK_a)
        m()->camera->coord.x -= 0.1;
    else if (k == XK_d)
        m()->camera->coord.x += 0.1;
    else if (k == XK_w)
        m()->camera->coord.y += 0.1;
    else if (k == XK_s)
        m()->camera->coord.y -= 0.1;
    else if (k == XK_Up)
    {
        rotate_x(0.2, &m()->camera->vector);
        m()->camera->theta.x += 0.2;
    }
    else if (k == XK_Down)
    {
        rotate_x(-0.2, &m()->camera->vector);
        m()->camera->theta.x -= 0.2;
    }
    else if (k == XK_Left)
    {
        rotate_y(-0.2, &m()->camera->vector);
        m()->camera->theta.y -= 0.2;
    }
    else if (k == XK_Right)
    {
        rotate_y(0.2, &m()->camera->vector);
        m()->camera->theta.y += 0.2;
    }
	else if (!(*who_movin()) && !(*which_light()) && (k == XK_minus || k == 65453) && m()->ambient->light_ratio > .1)
		m()->ambient->light_ratio -= .1;
	else if (!(*who_movin()) && !(*which_light()) && (k == XK_plus || k == 65451) && m()->ambient->light_ratio < .9)
		m()->ambient->light_ratio += .1;
    else
        return (0);
//    m()->camera->theta = find_theta((t_coord){0, 0, 1}, m()->camera->vector);
    // printf("======theta======\n");
    // print_coords(m()->camera->theta);
    return (1);
}

int	handle_keys(int k)
{
	int	to_render;
	
	to_render = 0;
	if (k == XK_Escape)
		ft_close(mlx());
	if (k == XK_l && toggle_select_light())
		to_render = 1;
    if ((*who_movin()) && !move_body(k))
		return (0);
	if ((*which_light()) && !to_render && !move_light(k))
		return (0);
    if ((!*who_movin() && !*which_light()) && !move_camera(k))
		return (0);
    if (N_THREADS == 1)
        render();
    else if (N_THREADS > 1)
    {
        array(m()->threads)->for_each(init_threads, 0);
        array(m()->threads)->for_each(join_for_each, 0);
        array(m()->threads)->for_each(imgs_to_canvas, 0);
        mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
    }
    return (1);
}
