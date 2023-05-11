/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:28 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/11 18:04:35 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_elems	**which_light(void)
{
	static t_elems	*which;

	return (&which);
}

void	**who_movin(void)
{
	static void	*who;

	return (&who);
}
