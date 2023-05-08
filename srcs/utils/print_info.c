/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:07:34 by touteiro          #+#    #+#             */
/*   Updated: 2023/05/08 20:40:59 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	reset_color(void)
{
	printf("\033[0m");
}

void	print_red(void)
{
	printf("\033[1;31m");
}

void	print_blue(void)
{
	printf("\033[1;34m");
}

void	print_info(void)
{
	print_red();
	printf("---------------------	USAGE	---------------------\n\n");
	reset_color();
	print_blue();
	printf("Select object with left click\n");
	reset_color();
	printf("Move object:			W A S D Up Down\n");
	printf("Rotate X-Axis:			B H\n");
	printf("Rotate Y-Axis:			N J\n");
	printf("Rotate Z-Axis:			M K\n");
	printf("Change sphere diameter:		R T\n");
	print_blue();
	printf("\nSelect lights with L\n");
	reset_color();
	printf("Change selected:		Left / Right\n");
	printf("Move light:			W A S D Up Down\n");
	printf("Change brightness:		Plus / Minus\n");
	print_blue();
	printf("\nIf no objects or lights are selected, camera is selected\n");
	reset_color();
	printf("Move camera:			W A S D\n");
	printf("Look left/right:		Left / Right\n");
	printf("Look up/down: 			Up / Down\n");
	printf("Change ambient brightness:	Plus / Minus\n");
}
