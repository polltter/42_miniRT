/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:56:14 by touteiro          #+#    #+#             */
/*   Updated: 2023/04/18 20:21:00 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	canvas_to_viewport(double x, double y)
{
	t_coord new;

	new.x = x * .001;
	new.y = y * .001;
	new.z = 1;
	return (new);
}

double	dot_product(t_coord a, t_coord b)
{
	double result = 0;
	result += (a.x * b.x);
	result += (a.y * b.y);
	result += (a.z * b.z);
	return (result);
}

t_point sphere_collision(t_coord O, t_coord D, t_sphere sphere)
{
	double r = sphere.diameter / 2;
	t_coord	CO;
	CO.y = O.y - sphere.coord.y;
	CO.z = O.z - sphere.coord.z;
	CO.x = O.x - sphere.coord.x;
	// printf("%f %f %f\n", D.x, D.y, D.z);
		// exit(1);
	// printf("%f %f %f\n", CO.x, CO.y, CO.z);
	double a = dot_product(D, D);
	double b = 2 * dot_product(CO, D);
	double c = dot_product(CO, CO) - pow(r, 2);
	// printf("%f %f %f\n", a, b, c);
	
	double discriminant = (b * b) - (4*a*c);
	// printf("%f\n", discriminant);
	if (discriminant < 0)
		return ((t_point){INT_MAX, INT_MAX});
	
	t_point new;
	new.x = (-b + sqrt(discriminant)) / (2 * a);
	new.y = (-b - sqrt(discriminant)) / (2 * a);
	// printf("%f %f\n", new.x, new.y);
	return (new);
}

int	trace_ray(t_coord O, t_coord D, double t_min, double t_max)
{
	double	closest_t = INT_MAX;
	t_sphere	*closest = NULL;
	t_point	t;

	t_elems	*temp;
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
	return (closest->color);
}

int	render(t_mlx_data *data)
{
	(void)data;

	t_coord		O;
	t_camera	C;
	t_sphere	sphere;
	
	O.x = 0;
	O.y = 0;
	O.z = 0;

	C.coord = O;
	C.id = 1;
	// C.vector.x = ((O.x * IMG_W / IMG_W), 0);
	// C.vector.x = ((O.y * IMG_H / IMG_H), 1);
	// C.vector.z = 10;

	sphere.id = 2;
	sphere.color = get_rgb(255, 0, 0);
	sphere.coord.x = -40;
	sphere.coord.y = -1;
	sphere.coord.z = 100;
	sphere.diameter = 2;

	double start_x = -IMG_W / 2;
	double end_x = IMG_W / 2;
	double start_y = -IMG_H / 2;
	double end_y = IMG_H / 2;
	t_coord	D;
	int		color;
	while (start_x < end_x)
	{
		while (start_y < end_y)
		{
			D = canvas_to_viewport(start_x, start_y);
			// printf("%f\n", D.x);
			color = trace_ray(O, D, 1, INT_MAX);
			// printf("%f %f\n", convert_point(start_x, 0), convert_point(start_y, 1));
			if (convert_point(start_x, 0) >= 0 && convert_point(start_x, 0) < IMG_W && \
				convert_point(start_y, 1) >= 0 && convert_point(start_y, 1) < IMG_H)
			{
				
				my_pixel_put(&mlx()->img, convert_point(start_x, 0), convert_point(start_y, 1), color);
			}
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
	// mlx_hook(data.mlx_win, 17, 0, ft_close, &data);
	// mlx_hook(mlx()->mlx_win, 2, 1l << 0, handle_keys, NULL);
	
	m()->spheres = creat_array();
	array(m()->spheres)->add((void *)(&(t_sphere){1, get_rgb(255, 0, 0), (t_coord){0, -1, 10}, 2}))->del = NULL;
	array(m()->spheres)->add((void *)(&(t_sphere){1, get_rgb(0, 255, 0), (t_coord){1, 0, 25}, 2}))->del = NULL;
	array(m()->spheres)->add((void *)(&(t_sphere){1, get_rgb(0, 0, 255), (t_coord){-1, 0, 4}, 2}))->del = NULL;
	
	
	mlx_mouse_hook(mlx()->mlx_win, handle_mouse, &data);
	mlx_loop_hook(mlx()->mlx, render, &data); //hook that is triggered when there's no event processed
	mlx_key_hook(mlx()->mlx_win, handle_keys, &data); //Mais facil de ler
	mlx_hook(mlx()->mlx_win, DestroyNotify, 0, ft_close, &data); //Mais facil de ler
	mlx_loop(data.mlx);
	return (0);

}
