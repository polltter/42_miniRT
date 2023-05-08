/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:48:53 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:53:29 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char *file_path)
{
	int	fd;

	if (!s().end_with(file_path, ".rt"))
		error("Invalid file");
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error("Invalid file");
	return (fd);
}

char	*space_str(void)
{
	return (" \t\n\v\f\r");
}
