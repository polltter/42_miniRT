/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/19 14:44:50 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniRT.h"

double	compute_lighting();

t_coord	canvas_to_viewport(double x, double y)
{
	t_coord	new;

	new.x = x / IMG_W;
	new.y = y / IMG_H;
	new.z = 1;
	return (new);
}
#include "../incs/miniRT.h"

double	dot_product(t_coord a, t_coord b)
{
	double	result;

	result = 0;
	result += (a.x * b.x);
	result += (a.y * b.y);
	result += (a.z * b.z);
	return (result);
}

void	print_coords(t_coord coord)
{
	printf("%f %f %f\n", coord.x, coord.y, coord.z);
}

double	compute_lighting(t_coord point, t_coord normal)
{
	double 	i;
	double	n_dot_l;
	t_elems *temp;
	t_coord	light;

	i = 0.0;
	temp = array(m()->lights)->begin;
	i += m()->ambient.light_ratio;
	while (temp)
	{
		light = do_op_coords(SUBTRACT, (*(t_light *)temp->cont).coord, point);
		n_dot_l = dot_product(normal, light);
		// printf("%f\n", (*(t_light *)temp->cont).light_ratio);
		if (n_dot_l > 0)
			i += (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
		temp = temp->next;
	}
	// printf("%d\n", get_rgb(0, 0, 255));
	// printf("%f\n", i);
	// printf("%f\n", get_rgb(0, 0, 255) * i);
	// exit(0);
	return(i);
}

t_coord	canvas_to_viewport(double x, double y)
{
	t_coord	new;

	new.x = x / IMG_W;
	new.y = y / IMG_H;
	new.z = 1;
	return (new);
}

t_point sphere_collision(t_coord O, t_coord D, t_sphere sphere)
{
	double	r;
	t_coord	CO;
	t_point	new;

	r = sphere.diameter / 2;
	CO = do_op_coords(SUBTRACT, O, sphere.coord);
	double a = dot_product(D, D);
	double b = 2 * dot_product(CO, D);
	double c = dot_product(CO, CO) - pow(r, 2);
	double discriminant = (b * b) - (4*a*c);
	if (discriminant < 0)
		return ((t_point){INT_MAX, INT_MAX});
	new.x = (-b + sqrt(discriminant)) / (2 * a);
	new.y = (-b - sqrt(discriminant)) / (2 * a);
	return (new);
}

int get_color_light(int color, double li)
{
    int r;
    int g;
    int b;

    r = (color >> 16 & 255) * li;
    g = (color >> 8 & 255) * li;
    b = (color >> 0 & 255) * li;
    return (get_rgb(r, g, b));
}

int	trace_ray(t_coord O, t_coord D, double t_min, double t_max)
{
	double		closest_t;
	t_sphere	*closest;
	t_point		t;
	t_elems		*temp;

	closest = NULL;
	closest_t = INT_MAX;
	temp = array(m()->spheres)->begin;
	while (temp)
	{
		t = sphere_collision(O, D, *(t_sphere *)(temp->cont));
		if (t.x > t_min && t.x < t_max && t.x < closest_t)
		{
			closest_t = t.x;
			closest = (t_sphere *)(temp->cont);
		}
		if (t.y > t_min && t.y < t_max && t.y < closest_t)
		{
			closest_t = t.y;
			closest = (t_sphere *)(temp->cont);
		}
		temp = temp->next;
	}
	if (!closest)
		return (get_rgb(255, 255, 255));

	t_coord	point = do_op_coords(ADD, O, coord_constant_op(MULTIPLY, D, closest_t));
	t_coord normal = do_op_coords(SUBTRACT, point, closest->coord);
	normal = coord_constant_op(DIVIDE, normal, vector_length(normal));
	// if (closest->color * compute_lighting(point, normal) > get_rgb(255, 255, 255))
		// return (get_rgb(255, 255, 255));

	return (get_color_light(closest->color, compute_lighting(point, normal)));
}

int	render(t_mlx_data *data)
{
	t_camera	camera;
	double		start_x;
	double		start_y;
	t_coord		D;
	int			color;

	(void)data;
	camera.coord = (t_coord){0, 0, 0};
	// camera.coord = set_coord_values(0, 0, 0);
	camera.vector = set_coord_values(0, 0, 0);
	camera.id = 1;
	start_x = -IMG_W / 2;
	start_y = -IMG_H / 2;
	while (start_x < IMG_W / 2)
	{
		while (start_y < IMG_H / 2)
		{
			D = canvas_to_viewport(start_x, start_y);
			color = trace_ray(camera.coord, D, 1, INT_MAX);
			if (convert_point(start_x, 0) >= 0 && convert_point(start_x, 0) < IMG_W && \
				convert_point(start_y, 1) >= 0 && convert_point(start_y, 1) < IMG_H)
				my_pixel_put(&mlx()->img, convert_point(start_x, 0), convert_point(start_y, 1), color);
			start_y += 1.0;
		}
		start_y = -IMG_H / 2;
		start_x += 1.0;
	}
	mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, mlx()->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;

	data_init(&data);
	*mlx() = data;
	m()->spheres = creat_array();
//	(array(m()->spheres))->add((void *)(&(t_sphere){2, get_rgb(255, 0, 0), (t_coord){0, -1, 10}, 2}))->del = NULL;
//	(array(m()->spheres))->add((void *)(&(t_sphere){2, get_rgb(0, 255, 0), (t_coord){1, 0, 25}, 2}))->del = NULL;
//	(array(m()->spheres))->add((void *)(&(t_sphere){2, get_rgb(0, 0, 255), (t_coord){-1, 0, 4}, 2}))->del = NULL;
//	m()->ambient = (t_default_light){1, 0.2, get_rgb(255, 255, 255)};
//	m()->lights = creat_array();
//	array(m()->lights)->add((void *)(&(t_light){1, .6, get_rgb(255, 255, 255), (t_coord){2, 1, 0}}));
    array(m()->spheres)->add(build("sp 0,-1,3 2 255,0,0"));
    array(m()->spheres)->add(build("sp 2,0,4 1 0,0,255"));
    array(m()->spheres)->add(build("sp -2,0,4 1 0,255,0"));
	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
	mlx_loop_hook(mlx()->mlx, render, &data);
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data);
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
