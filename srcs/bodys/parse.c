/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:48:53 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/09 18:27:30 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char *file_path)
{
	int	fd;

	if (!s().end_with(file_path, ".rt"))
		error("Invalid file\n");
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error("Invalid file\n");
	return (fd);
}

char	*space_str(void)
{
	return (" \t\n\v\f\r");
}

void	check_scene(void)
{
	if (!array(m()->bodys)->size)
		error("Scene must have at least one body!\n");
	else if (!m()->ambient)
		error("Scene must have an ambient light!\n");
	else if (!m()->camera)
		error("Scene must have a camera!\n");
}
