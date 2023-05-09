/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 18:52:26 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	help_ambient_light(char *input, int id)
{
	if (m()->ambient)
		build_error(input, NULL, "Scene can only have one ambient light!\n");
	(m()->ambient) = build_ambient_light(input, id);
	if (!m()->ambient)
		build_error(input, NULL, "");
}

void	help_lights(char *input, int id)
{
	int	lights;

	lights = (array(m()->lights))->size;
	(array(m()->lights))->add(build_light(input, id));
	if ((array(m()->lights))->size == lights)
		build_error(input, NULL, "");
}

void	help_camera(char *input, int id)
{
	if (m()->camera)
		build_error(input, NULL, "Scene can only have one camera!\n");
	(m()->camera) = build_camera(input, id);
	if (!m()->camera)
		build_error(input, NULL, "");
	(m()->camera)->theta = find_theta((t_coord){0, 0, 1}, \
							m()->camera->vector);
}

void	build_scene_helper(char *input)
{
	int	id;

	id = get_id(input);
	if (id == -1)
		build_error(input, NULL, "Not a valid identifier!\n");
	if (id >= SPH)
		(array(m()->bodys))->add(build(input, id));
	else if (id == AL)
		help_ambient_light(input, id);
	else if (id == L)
		help_lights(input, id);
	else if (id == C)
		help_camera(input, id);
}
