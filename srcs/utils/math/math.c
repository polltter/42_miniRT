/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:52:49 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/22 20:18:48 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	do_op(int op, double a, double b)
{
	if (op == ADD)
		return (a + b);
	else if (op == SUBTRACT)
		return (a - b);
	else if (op == MULTIPLY)
		return (a * b);
	else if (op == DIVIDE && b)
		return (a / b);
	return (0);
}

double	dot_product(t_coord a, t_coord b)
{
	double	result;

	result = 0;
	result += (a.x * b.x);
	result += (a.y * b.y);
	result += (a.z * b.z);
	return (result);
}

double	vector_length(t_coord vector)
{
	double	len;

	len = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (len);
}
