/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:47:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 16:24:20 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/miniRT.h"

t_body	*body(void *obj)
{
	*__this_body() = obj;
	return (*__this_body());
}

t_body	**__this_body(void)
{
	static t_body	*a;

	return (&a);
}

void	build_scene(char *file_path)
{
	int		fd;
	char	*input;

	fd = check_file(file_path);
	input = ft_calloc(1);
	m()->bodys = creat_array();
	m()->lights = creat_array();
	while (input)
	{
		free(input);
		input = get_next_line(fd);
		if (!s().equal(input, "\n") || !s().equal_n(input, "#", 1) || !input)
			continue ;
		build_scene_helper(input);
	}
	check_scene();
	free(input);
}
