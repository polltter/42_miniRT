/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:04:27 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/20 18:20:08 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_ambient_light	t_ambient_light;
typedef struct s_default_body	t_default_body;
typedef struct s_mlx_data		t_mlx_data;
typedef struct s_cylinder		t_cylinder;
typedef struct s_viewport       t_viewport;
typedef struct s_threads        t_threads;
typedef struct s_camera			t_camera;
typedef struct s_sphere			t_sphere;
typedef struct s_coord			t_coord;
typedef struct s_light			t_light;
typedef struct s_plane			t_plane;
typedef struct s_point			t_point;
typedef struct s_data			t_data;
typedef struct s_main			t_main;


enum e_types {
	AL,
	L,
	C,
	SPH,
	PL,
	CY,
};

struct s_viewport {
    double  width;
    double  height;
};

struct s_coord {
	double	x;
	double	y;
	double	z;
};

struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
};

struct s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	t_data		img;
};

struct s_ambient_light {
	int		id;
	double	light_ratio;
	int		color;
};

struct s_light {
	int		id;
	double	light_ratio;
	int		color;
	t_coord	coord;
};

struct s_camera {
	int     id;
	t_coord coord;
	t_coord vector;
	int		fov;
};

struct s_default_body {
    int     id;
    int     color;
    t_coord coord;
    double	specular;
    double	reflective;
};

struct s_sphere {
    int     id;
    int     color;
    t_coord coord;
    double	specular;
    double	reflective;
    double  diameter;
};

struct s_plane {
    int     id;
    int     color;
    t_coord coord;
    double	specular;
    double	reflective;
	t_coord vector;
};

struct s_cylinder {
    int     id;
    int     color;
    t_coord coord;
    double	specular;
    double	reflective;
	t_coord vector;
	double  diameter;
	double  height;
};

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

struct s_main {
	void			*bodys;
	t_ambient_light	*ambient;
	void			*lights;
    t_camera        *camera;
    t_viewport      viewport;
    t_coord         v_dir;
    void            *threads;
    pthread_mutex_t draw;
};

struct s_threads {
    pthread_t   id;
    int         strat_x;
    int         end_x;
    t_data      img;
};

#endif
