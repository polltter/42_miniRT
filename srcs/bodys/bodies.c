/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bodys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:54:35 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 16:25:41 by touteiro         ###   ########.fr       */
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
	(*__this_body())->coord = get_coord(details[i], (float)(10000));
	while (details[i])
		i++;
	(*__this_body())->color = get_color(details[--i]);
	(*__this_body())->original_color = (*__this_body())->color;
	(*__this_body())->reflective = ft_atod(details[--i], 1);
	(*__this_body())->specular = ft_atod(details[--i], 10000);
	if (((*__this_body())->coord.x == INT_MAX && \
		(*__this_body())->coord.y == INT_MAX && \
		(*__this_body())->coord.x == INT_MAX) || \
		(*__this_body())->color == -1 || \
		(*__this_body())->reflective == INT_MAX || \
		((*__this_body())->reflective < 0 && \
		printf("Reflective value can\'t be negative\n")) || \
		(*__this_body())->specular == INT_MAX || \
		((*__this_body())->specular < 0 && \
		printf("Specular value can\'t be negative\n")))
		return (0);
	return (1);
}

int	build_sphere(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
	{
		freepp((void **)details);
		printf("Wrong number of arguments for sphere\n");
		return (0);
	}
	if (!build_default_body(details))
	{
		freepp((void **)details);
		return (0);
	}
	((t_sphere *)(*__this_body()))->diameter = \
			ft_atod(*(details + 2), (float)(1000000000));
	if (((t_sphere *)(*__this_body()))->diameter == INT_MAX)
	{
		freepp((void **)details);
		return (0);
	}
	freepp((void **)details);
	return (1);
}

int	build_plane(char *input)
{
	char	**details;
	t_coord	vector;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
	{
		freepp((void **)details);
		error("Wrong number of arguments");
	}
	if (!build_default_body(details))
	{
		freepp((void **)details);
		return (0);
	}
	((t_plane *)(*__this_body()))->vector = get_coord(*(details + 2), 1.0);
	freepp((void **)details);
	vector = ((t_plane *)(*__this_body()))->vector;
	if (vector.x == INT_MAX || vector.y == INT_MAX || vector.z == INT_MAX)
		return (0);
	return (1);
}

int	build_cylinder(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3) || \
		!*(details + 4) || !*(details + 5))
	{
		freepp((void **)details);
		error("Wrong number of arguments");
	}
	if (!build_plane(input))
	{
		freepp((void **)details);
		return (0);
	}
	((t_cylinder *)(*__this_body()))->diameter = \
			ft_atod(details[3], (float)1000000000);
	((t_cylinder *)(*__this_body()))->height = \
			ft_atod(details[4], (float)1000000000);
	freepp((void **)details);
	if (((t_cylinder *)(*__this_body()))->diameter == INT_MAX || \
		((t_cylinder *)(*__this_body()))->height == INT_MAX)
		return (0);
	return (1);
}
