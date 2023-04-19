//
// Created by miguel on 17-04-2023.
//

#include "miniRT.h"

t_default_body  **___this(void)
{
    static t_default_body	*a;

    return (&a);
}

t_default_body	*body(void *obj)
{
    *___this() = obj;
    return (*___this());
}

int get_color(char *color)
{
    char    **colors;
    int     r;
    int     g;
    int     b;

    colors = s().split(color, ',');
    if (!*colors || !*(colors + 1) || !*(colors + 2))
	{
		freepp((void **)colors);
		error("Wrong number of arguments");
	}
    r = ft_atoi(colors[0], 255);
    g = ft_atoi(colors[1], 255);
    b = ft_atoi(colors[2], 255);
	if (r < 0 || g < 0 || b < 0)
	{
		freepp((void **)colors);
		error("Invalid color");
	}
    freepp((void **)colors);
    return (get_rgb(r, g, b));
}

t_coord get_coord(char *s_coords, float max)
{
    char    **coords;
    t_coord coord;

    coords = s().split(s_coords, ',');
    if (!*coords || !*(coords + 1) || !*(coords + 2))
        error("Wrong number of arguments");
    coord.x = ft_atod(coords[0], max);
    coord.y = ft_atod(coords[1], max);
    coord.z = ft_atod(coords[2], max);
    freepp((void **)coords);
    return (coord);
}

int get_id(char *s_id)
{
    if (!s().equal(s_id, "sp"))
        return (SPH);
    else if (!s().equal(s_id, "pl"))
        return (PL);
    else if (!s().equal(s_id, "cy"))
        return (CY);
    error("Not a valid body");
    return (0);
}

void    build_default_body(char **details)
{
    int i;
    i = 1;
    (*___this())->id = get_id(*details);
    (*___this())->coord = get_coord(details[i], (float)INT_MAX);
    while (details[i])
        i++;
    (*___this())->color = get_color(details[--i]);
}

void    build_sphere(char *input)
{
    char    **details;

    details = s().split(input, ' ');
    if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
        error("Wrong number of arguments");
    build_default_body(details);
    ((t_sphere *)(*___this()))->diameter = ft_atod(*(details + 2), (float)INT_MAX);
	freepp((void **)details);
}

void    build_plane(char *input)
{
	char    **details;

	details = s().split(input, ' ');
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
		error("Wrong number of arguments");
	build_default_body(details);
	((t_plane *)(*___this()))->vector = get_coord(*(details + 2), 1.0);
	freepp((void **)details);
}

void    build_cylinder(char *input)
{
	char    **details;

	details = s().split(input, ' ');
	if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3) || \
		!*(details + 4) || !*(details + 5))
		error("Wrong number of arguments");
	build_plane(input);
	((t_cylinder *)(*___this()))->diameter = ft_atod(details[3], (float)INT_MAX);
	((t_cylinder *)(*___this()))->height = ft_atod(details[4], (float)INT_MAX);
	freepp((void **)details);
}