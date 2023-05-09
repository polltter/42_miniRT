/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bodys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:54:35 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 13:40:06 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_body	**__this_body(void)
{
	static t_body	*a;

	return (&a);
}

int	build_default_body(char **details)
{
	int	i;

	i = 1;
	(*__this_body())->id = get_id(*details);
	(*__this_body())->coord = get_coord(details[i], (float)(1000000000));
	if ((*__this_body())->coord.x == INT_MAX && \
		(*__this_body())->coord.y == INT_MAX && \
		(*__this_body())->coord.x == INT_MAX)
	{
		freepp((void **)details);
		return (0);
	}
	while (details[i])
		i++;
	(*__this_body())->color = get_color(details[--i]);
	(*__this_body())->original_color = (*__this_body())->color;
	(*__this_body())->reflective = ft_atod(details[--i], 1);
	(*__this_body())->specular = ft_atod(details[--i], 10000);
	return (1);
}

int	build_sphere(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
	{
		freepp((void **)details);
		printf("Wrong number of arguments");
		return (0);
	}
	if (!build_default_body(details))
	{
		freepp((void **)details);
		free(input);
		return (0);
	}
	((t_sphere *)(*__this_body()))->diameter = \
			ft_atod(*(details + 2), (float)(1000000000));
	if (((t_sphere *)(*__this_body()))->diameter == INT_MAX)
	{
		freepp((void **)details);
		free(input);
		return (0);
	}
	freepp((void **)details);
	return (1);
}

void	build_plane(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
	{
		freepp((void **)details);
		error("Wrong number of arguments");
	}
	build_default_body(details);
	((t_plane *)(*__this_body()))->vector = get_coord(*(details + 2), 1.0);
	freepp((void **)details);
}

void	build_cylinder(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3) || \
		!*(details + 4) || !*(details + 5))
	{
		freepp((void **)details);
		error("Wrong number of arguments");
	}
	build_plane(input);
	((t_cylinder *)(*__this_body()))->diameter = \
			ft_atod(details[3], (float)INT_MAX);
	((t_cylinder *)(*__this_body()))->height = \
			ft_atod(details[4], (float)INT_MAX);
	freepp((void **)details);
}
