/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:04:06 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/18 20:11:35 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "list_utils.h"
# include "structs.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "stdio.h"
# include <math.h>
# include <limits.h>

# define IMG_W 1000
# define IMG_H 1000

//MLX utils
t_mlx_data	*mlx(void);
t_main		*m(void);
void		data_init(t_mlx_data *data);
int			ft_close(t_mlx_data *data);
void		my_pixel_put(t_data *img, int x, int y, int color);

//Draw utils
double			convert_point(double x, double is_Y);
int			get_rgb(int r, int g, int b);

//Handles
int			handle_keys(int k);
int			handle_mouse(int button, int x, int y, t_mlx_data *data);

#endif
