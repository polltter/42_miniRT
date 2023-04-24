/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:04:06 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/24 17:09:25 by touteiro         ###   ########.fr       */
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
# define N_THREADS  13

//MLX utils
t_mlx_data	*mlx(void);
t_main		*m(void);
void		data_init(t_mlx_data *data);
int			ft_close(t_mlx_data *data);
void		my_pixel_put(t_data *img, int x, int y, int color);

//Draw utils
t_coord		canvas_to_viewport(double x, double y);
double		vp_to_canvas(double x, double is_Y);

//Color manipulation
int			get_rgb(int r, int g, int b);
int			get_color_light(int color, t_coord li);
int			multiply_color(int color, double brightness);
double		multiply_component(int color, int shift, double brightness);

//Struct utils
t_coord		set_coord_values(double x, double y, double z);
t_coord		coord_constant_op(int op, t_coord coord, double constant);
t_coord		do_op_coords(int op, t_coord a, t_coord b);
double		vector_length(t_coord vector);
double	    ft_atod(char *str, double max);
int	        ft_atoi(char *nptr, int max);
void        freepp(void **to_free);

//Render
int			render(t_mlx_data *data);
int			trace_ray(t_coord O, t_coord viewport_pt, double t_min, double t_max, int recursion_depth);
t_coord		reflect_ray(t_coord light, t_coord normal);
t_coord		compute_lighting(t_coord point, t_coord normal, t_coord vector, double specular);

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
t_ambient_light *build_ambient_light(char *input, int id);
void    *build_light(char *input, int id);

//rotations
t_point find_theta(void);
void  rotate_camera(t_point theta, t_coord *vp_to_canvasviewport_pt);

//Math
double	dot_product(t_coord a, t_coord b);
double	do_op(int op, double a, double b);

//Collisions
t_sphere	*closest_intersection(t_coord O, t_coord viewport_pt, double t_min, double t_max, double *closest_t);
int			in_shadow(t_coord O, t_coord viewport_pt, double t_min, double t_max);
t_point		collision(t_coord O, t_coord viewport_pt, t_default_body *body);
t_point 	sphere_collision(t_coord O, t_coord viewport_pt, t_sphere sphere);

//threads
void    build_threads(void);
void	join_for_each(t_elems *elem, void *o);
void	init_threads(t_elems *elem, void *o);
void	print_threads(t_elems *elem, void *o);
void    imgs_to_canvas(t_elems *elem, void *o);

//render
void    *render_t(void *t);
t_elems **first(void);
t_elems **first_l(void);

//debugging
void	print_coords(t_coord coord);


#endif
