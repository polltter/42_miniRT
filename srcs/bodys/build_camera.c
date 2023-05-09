/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:02:12 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 17:03:04 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	camera_check(t_camera *camera)
{
	if ((camera->coord.x == INT_MAX && camera->coord.y == INT_MAX && \
		camera->coord.z == INT_MAX) || (camera->vector.x == INT_MAX && \
		camera->vector.y == INT_MAX && camera->vector.z == INT_MAX))
		return (0);
	if ((camera->fov > 180 || camera->fov < 0) && \
		printf("Invalid value for FOV!\n"))
		return (0);
	return (1);
}

t_camera	*build_camera(char *input, int id)
{
	char		**details;
	t_camera	*camera;

	details = s().split(input, space_str());
	if (arr_size((void **)details) != 4)
	{
		freepp((void **)details);
		printf("Wrong number of camera inputs!\n");
		return (0);
	}
	camera = ft_calloc(sizeof(t_camera));
	camera->id = id;
	camera->coord = get_coord(details[1], (float)1000000000);
	camera->vector = get_coord(details[2], 1);
	camera->fov = ft_atoi(details[3], 180);
	freepp((void **)details);
	m()->viewport.height = IMG_H / IMG_H;
	m()->viewport.width = 2 * tan(camera->fov / 2.0 * M_PI / 180.0);
	if (!camera_check(camera))
	{
		free(camera);
		return (0);
	}
	return (camera);
}
