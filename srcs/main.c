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

# define SHINY 11.75 //for specular reflection

t_sphere	*closest_intersection(t_coord O, t_coord D, double t_min, double t_max, double *closest_t);
void    **who_movin(void);

double	compute_lighting();

t_coord	canvas_to_viewport(double x, double y)
{
	static t_coord	new;

	new.x = x / IMG_W * m()->viewport.width;
	new.y = y / IMG_H * m()->viewport.height;
	new.z = 1;
	return (new);
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

void	print_coords(t_coord coord)
{
	printf("%f %f %f\n", coord.x, coord.y, coord.z);
}

t_coord	reflect_ray(t_coord light, t_coord normal)
{
	return (do_op_coords(SUBTRACT, coord_constant_op(MULTIPLY, coord_constant_op(MULTIPLY, normal, 2), dot_product(normal, light)), light));
}

double	compute_lighting(t_coord point, t_coord normal, t_coord vector, double specular)
{
	double 	i;
	double	n_dot_l;
	double	r_dot_v;
	double		shadow_t;
	t_sphere	*shadow_sphere;
	t_elems *temp;
	t_coord	light;
	t_coord	reflected;

	i = 0.0;
	temp = array(m()->lights)->begin;
	i += m()->ambient.light_ratio;
	while (temp)
	{
		light = do_op_coords(SUBTRACT, (*(t_light *)temp->cont).coord, point);
		//Shadow check
		shadow_t = INT_MAX;
		shadow_sphere = closest_intersection(point, light, .001, INT_MAX, &shadow_t);
		if (shadow_sphere)
		{
			temp = temp->next;
			continue ;
		}
		//Compute diffusion
		n_dot_l = dot_product(normal, light);
		if (n_dot_l > 0)
			i += (*(t_light *)temp->cont).light_ratio * n_dot_l / (vector_length(normal) * vector_length(light));
		//Compute reflection
		if (specular > 0)
		{
			reflected = reflect_ray(light, normal);
			r_dot_v = dot_product(reflected, vector);
			if (r_dot_v > 0)
				i += (*(t_light *)temp->cont).light_ratio * pow(r_dot_v / (vector_length(reflected) / vector_length(vector)), specular);
		}
		temp = temp->next;
	}
	if (i > 1) // Incorrect, needs to be improved
		i = 1;
	return(i);
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

t_sphere	*closest_intersection(t_coord O, t_coord D, double t_min, double t_max, double *closest_t)
{
	t_elems		*temp;
	t_point		t;
	t_sphere	*closest;

	temp = array(m()->bodys)->begin;
	closest = NULL;
	while (temp)
	{
		t = sphere_collision(O, D, *(t_sphere *)(temp->cont));
		if (t.x > t_min && t.x < t_max && t.x < *closest_t)
		{
			*closest_t = t.x;
			closest = (t_sphere *)(temp->cont);
		}
		if (t.y > t_min && t.y < t_max && t.y < *closest_t)
		{
			*closest_t = t.y;
			closest = (t_sphere *)(temp->cont);
		}
		temp = temp->next;
	}
	return (closest);
}

int	trace_ray(t_coord O, t_coord D, double t_min, double t_max, int recursion_depth)
{
	double		closest_t;
	t_sphere	*closest;
	double		reflective;
	int			local_color;
	int			reflected_color;
	t_coord		mirror;

	closest_t = INT_MAX;
	closest = closest_intersection(O, D, t_min, t_max, &closest_t);
	if (!closest)
		return (get_rgb(255, 255, 255));

	t_coord	point = do_op_coords(ADD, O, coord_constant_op(MULTIPLY, D, closest_t));
	t_coord normal = do_op_coords(SUBTRACT, point, closest->coord);
	normal = coord_constant_op(DIVIDE, normal, vector_length(normal));
	local_color = get_color_light(closest->color, compute_lighting(point, normal, coord_constant_op(MULTIPLY, D, -1), closest->specular));

	reflective = closest->reflective;
	if (recursion_depth <= 0 || reflective <= 0)
		return (local_color);
	mirror = reflect_ray(coord_constant_op(MULTIPLY, D, -1), normal);
	reflected_color = trace_ray(point, mirror, .001, INT_MAX, recursion_depth - 1);
	return (get_color_light(local_color, (1 - reflective)) + get_color_light(reflected_color, reflective));
	// return (local_color * (1 - reflective) + reflected_color * reflective);
}

int store_colors(int color, int flag)
{
    static int r;
    static int g;
    static int b;
    static int counter;
    int        c;

    if (!flag)
    {
        r += color >> 16 & 255;
        g += color >> 8 & 255;
        b += color >> 0 & 255;
        counter++;
    }
    else
    {
        c = get_rgb(r / counter, g / counter, b / counter);
        r = 0;
        g = 0;
        b = 0;
        counter = 0;
        return (c);
    }
    return (0);
}

int	render(t_mlx_data *data)
{
	double		start_x;
	double		start_y;
	t_coord		D;
    t_point     theta;
	int			color;

    theta = find_theta();
    m()->camera.id = C;
	start_x = -IMG_W / 2;
	start_y = -IMG_H / 2;
	while (start_x < IMG_W / 2)
	{
		while (start_y < IMG_H / 2)
		{
            D = canvas_to_viewport(start_x, start_y);
            rotate_camera(theta, &D);
            color = trace_ray(m()->camera.coord, D, 1, INT_MAX, 3);
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

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data_init(&data);
	*mlx() = data;
    build_scene(av[ac - 1]);
//	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
    render(NULL);
	mlx_mouse_hook(mlx()->mlx_win, select_body, &data);
//	mlx_loop_hook(mlx()->mlx, render, &data);
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data);
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
