/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:04:06 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/19 15:27:04 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "get_next_line.h"
# include "list_utils.h"
# include "ft_strings.h"
# include "structs.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "stdio.h"
# include "stdlib.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

# define IMG_W 1000
# define IMG_H 1000
# define ADD		100
# define SUBTRACT	101
# define MULTIPLY	102
# define DIVIDE		103
# define N_THREADS  2

//MLX utils
t_mlx_data	*mlx(void);
t_main		*m(void);
void		data_init(t_mlx_data *data);
int			ft_close(t_mlx_data *data);
void		my_pixel_put(t_data *img, int x, int y, int color);

//Draw utils
double		convert_point(double x, double is_Y);
int			get_rgb(int r, int g, int b);

//Struct utils
t_coord		set_coord_values(double x, double y, double z);
t_coord		coord_constant_op(int op, t_coord coord, double constant);
t_coord		do_op_coords(int op, t_coord a, t_coord b);
double		vector_length(t_coord vector);
double	    ft_atod(char *str, double max);
int	        ft_atoi(char *nptr, int max);
void        freepp(void **to_free);

//Handles
int			handle_keys(int k);
int			handle_mouse(int button, int x, int y, t_mlx_data *data);
int	        select_body(int button, int x, int y, t_mlx_data *data);

//error_management/error.c
int    error(char *err);

//bodys/build
void    *build(char *input, int id);
void    build_scene(char *file_path);

//bodys/build_bodys
t_default_body  **__this_body(void);
void            build_default_body(char **details);
void            build_sphere(char *input);
void            build_plane(char *input);
void             build_cylinder(char *input);

//bodys/build_butils
t_default_body	*body(void *obj);
char            *space_str(void);
int             get_color(char *color);
t_coord         get_coord(char *s_coords, float max);
int             get_id(char *input);

//bodys/build_lights
t_ambient_light build_AL(char *input, int id);
void    *build_light(char *input, int id);

//rotations
t_point find_theta(void);
void  rotate_camera(t_point theta, t_coord *D);

//threads
void    build_threads(void);
void	join_for_each(t_elems *elem, void *o);
void	init_threads(t_elems *elem, void *o);
void	print_threads(t_elems *elem, void *o);

//render
void    *render(void *thread);
void	reload_threads(t_elems *elem, void *o);



#endif
