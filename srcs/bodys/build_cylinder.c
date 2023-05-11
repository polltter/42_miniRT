/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:38:02 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 16:38:27 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	build_cylinder_cap(t_plane *plane, t_coord center, t_coord vector)
{
	plane->vector = vector;
	normalize(&vector);
	plane->coord = do_op_coords(ADD, center, \
							coord_constant_op(MULTIPLY, \
							vector, \
							((t_cylinder *)(*__this_body()))->height / 2));
	plane->color = ((t_cylinder *)(*__this_body()))->color;
	plane->specular = ((t_cylinder *)(*__this_body()))->specular;
	plane->reflective = ((t_cylinder *)(*__this_body()))->reflective;
}

void	build_cylinder_caps(t_cylinder *cylinder)
{
	build_cylinder_cap(&(cylinder->top), cylinder->coord, cylinder->vector);
	build_cylinder_cap(&(cylinder->bottom), cylinder->coord, \
						coord_constant_op(MULTIPLY, cylinder->vector, -1));
}

int	build_cylinder(char *input)
{
	char	**details;

	details = s().split(input, space_str());
	if (arr_size((void **)details) < 6)
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
	build_cylinder_caps((t_cylinder *)(*__this_body()));
	return (1);
}
