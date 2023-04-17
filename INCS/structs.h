//
// Created by miguel on 17-04-2023.
//

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_default_light t_default_light;
typedef struct s_default_body t_default_body;
typedef struct s_mlx_data t_mlx_data;
typedef struct s_cylinder t_cylinder;
typedef struct s_camera t_camera;
typedef struct s_sphere t_sphere;
typedef struct s_coord t_coord;
typedef struct s_light t_light;
typedef struct s_plane t_plane;
typedef struct s_data t_data;

struct s_coord {
    double  x;
    double  y;
    double  z;
};

struct s_data {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
    int 	w;
    int		h;
};

struct s_mlx_data {
    void		*mlx;
    void		*mlx_win;
    t_data		img;
};

struct s_default_light {
    int     id;
    double  light_ratio;
    int     color;
};

struct s_light {
    int     id;
    double  light_ratio;
    int     color;
    t_coord coord;
};

struct s_camera {
    int     id;
    t_coord coord;
    t_coord vector;
};

struct s_default_body {
    int     id;
    int     color;
    t_coord coord;
};

struct s_sphere {
    int     id;
    int     color;
    t_coord coord;
    double  diameter;
};

struct s_plane {
    int     id;
    int     color;
    t_coord coord;
    t_coord vector;
};

struct s_cylinder {
    int     id;
    int     color;
    t_coord coord;
    t_coord vector;
    double  diameter;
    double  height;
};

#endif
