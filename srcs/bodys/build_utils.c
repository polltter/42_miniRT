/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:52:23 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 18:40:20 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

void	build_error(char *input, void *b, char*str)
{
	free(b);
	free(input);
	error(str);
}

int	get_color(char *color)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	colors = s().split(color, ",");
	if (!*colors || !*(colors + 1) || !*(colors + 2))
	{
		freepp((void **)colors);
		printf("Wrong number of arguments for colors\n");
		return (-1);
	}
	r = ft_atoi(colors[0], 255);
	g = ft_atoi(colors[1], 255);
	b = ft_atoi(colors[2], 255);
	if (r < 0 || g < 0 || b < 0 || \
		r == INT_MAX || g == INT_MAX || b == INT_MAX)
	{
		freepp((void **)colors);
		printf("Invalid color\n");
		return (-1);
	}
	freepp((void **)colors);
	return (get_rgb(r, g, b));
}

t_coord	get_coord(char *s_coords, float max)
{
	char	**coords;
	t_coord	coord;

	coords = s().split(s_coords, ",");
	if (!*coords || !*(coords + 1) || !*(coords + 2))
	{
		freepp((void **)coords);
		error("Wrong number of arguments");
	}
	coord.x = ft_atod(coords[0], max);
	coord.y = ft_atod(coords[1], max);
	coord.z = ft_atod(coords[2], max);
	freepp((void **)coords);
	if (coord.x == INT_MAX || coord.y == INT_MAX || coord.z == INT_MAX)
		return ((t_coord){INT_MAX, INT_MAX, INT_MAX});
	return (coord);
}

int	clean_id(char **s_id)
{
	freepp((void **)s_id);
	return (1);
}

int	get_id(char *input)
{
	char	**s_id;

	s_id = s().split(input, space_str());
	if (!*s_id)
		error("Wrong number of inputs\n");
	if (!s().equal(*s_id, "sp") && clean_id(s_id))
		return (SPH);
	else if (!s().equal(*s_id, "pl") && clean_id(s_id))
		return (PL);
	else if (!s().equal(*s_id, "cy") && clean_id(s_id))
		return (CY);
	else if (!s().equal(*s_id, "A") && clean_id(s_id))
		return (AL);
	else if (!s().equal(*s_id, "L") && clean_id(s_id))
		return (L);
	else if (!s().equal(*s_id, "C") && clean_id(s_id))
		return (C);
	clean_id(s_id);
	return (-1);
}
