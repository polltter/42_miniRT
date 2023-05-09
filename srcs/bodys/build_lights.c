/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:54:02 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 16:40:25 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_ambient_light	*build_ambient_light(char *input, int id)
{
	t_ambient_light	*new;
	char			**details;

	details = s().split(input, space_str());
	if (arr_size((void **)details) != 3)
	{
		freepp((void **)details);
		printf("Wrong number of inputs for ambient light\n");
		return (0);
	}
	new = ft_calloc(sizeof(t_ambient_light));
	new->id = id;
	new->light_ratio = ft_atod(details[1], 1.0);
	new->color = get_color(details[2]);
	freepp((void **)details);
	if (new->light_ratio == INT_MAX || \
		(new->light_ratio < 0 && printf("light ratio can\'t be negative\n")) || \
		new->color == -1)
	{
		free(new);
		return (0);
	}
	return (new);
}

void	*build_light(char *input, int id)
{
	t_light			*new;
	char			**details;

	details = s().split(input, space_str());
	if (arr_size((void **)details) != 4)
	{
		freepp((void **)details);
		printf("Wrong number of inputs for light point\n");
		return (0);
	}
	new = ft_calloc(sizeof(t_light));
	new->id = id;
	new->light_ratio = ft_atod(details[1], 1.0);
	new->coord = get_coord(details[2], (float)(1000000000));
	new->color = get_color(details[3]);
	freepp((void **)details);
	if (new->light_ratio == INT_MAX || new->color == -1 || \
		(new->light_ratio < 0 && printf("light ratio can\'t be negative\n")) || \
		(new->coord.x == INT_MAX && new->coord.x == INT_MAX && \
		new->coord.z == INT_MAX))
	{
		free(new);
		return (0);
	}
	return (new);
}
