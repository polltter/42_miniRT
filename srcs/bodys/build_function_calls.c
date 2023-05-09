/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:44:22 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 18:48:09 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*create_plane(void *b, char *input)
{
	b = ft_calloc(sizeof(t_plane));
	body(b);
	if (!build_plane(input))
		build_error(input, b, "");
	return (b);
}

void	*create_sphere(void *b, char *input)
{
	b = ft_calloc(sizeof(t_sphere));
	body(b);
	if (!build_sphere(input))
		build_error(input, b, "");
	return (b);
}

void	*create_cylinder(void *b, char *input)
{
	b = ft_calloc(sizeof(t_cylinder));
	body(b);
	if (!build_cylinder(input))
		build_error(input, b, "");
	return (b);
}

void	*build(char *input, int id)
{
	void	*b;

	b = NULL;
	if (id == PL)
		b = create_plane(b, input);
	else if (id == SPH)
		b = create_sphere(b, input);
	else if (id == CY)
		b = create_cylinder(b, input);
	else
		error("Wrong identifier.");
	return (b);
}
