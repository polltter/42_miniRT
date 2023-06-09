/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:51:43 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/12 16:45:30 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	toggle_select_light(void)
{
	static int	selected;

	if (!selected)
	{
		if (*who_movin())
		{
			((t_body *)(*who_movin()))->color = \
				((t_body *)(*who_movin()))->original_color;
			(*who_movin()) = NULL;
		}
		printf("selected light 1\n");
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

void	select_left(int selected)
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

void	select_right(int selected)
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

void	select_light(int k, t_light *temp)
{
	int	selected;

	selected = array(m()->lights)->index_of((void *)temp);
	if (k == XK_Right)
		select_right(selected);
	else if (k == XK_Left)
		select_left(selected);
}

int	move_light(int k)
{
	t_light		*temp;

	temp = (*which_light())->cont;
	if ((k == XK_minus || k == 65453) && temp->light_ratio > .1)
		temp->light_ratio -= .1;
	else if ((k == XK_plus || k == 65451) && temp->light_ratio < 1)
		temp->light_ratio += .1;
	else if (k == XK_Right || k == XK_Left)
		select_light(k, temp);
	else if (k == XK_a)
		temp->coord.x -= .1;
	else if (k == XK_d)
		temp->coord.x += .1;
	else if (k == XK_s)
		temp->coord.y -= .1;
	else if (k == XK_w)
		temp->coord.y += .1;
	else if (k == XK_Up)
		temp->coord.z += .5;
	else if (k == XK_Down)
		temp->coord.z -= .5;
	else
		return (0);
	return (1);
}
