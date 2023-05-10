//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

t_body  **__this_body(void)
{
    static t_body	*a;

    return (&a);
}

void    build_default_body(char **details)
{
    int i;
    i = 1;
    (*__this_body())->id = get_id(*details);
    (*__this_body())->coord = get_coord(details[i], (float)(1000000000));
    while (details[i])
        i++;
    (*__this_body())->color = get_color(details[--i]);
    (*__this_body())->reflective = ft_atod(details[--i], 1);
    (*__this_body())->specular = ft_atod(details[--i], 10000);
}

void    build_sphere(char *input)
{
    char    **details;

    details = s().split(input, space_str());
    if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
        error("Wrong number of arguments");
    build_default_body(details);
    ((t_sphere *)(*__this_body()))->diameter = ft_atod(*(details + 2), (float)(1000000000));
    freepp((void **)details);
}

void    build_plane(char *input)
{
    char    **details;

    details = s().split(input, space_str());
    if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3))
        error("Wrong number of arguments");
    build_default_body(details);
    ((t_plane *)(*__this_body()))->vector = get_coord(*(details + 2), 1.0);
    freepp((void **)details);
}

void    build_cylinder_caps(t_plane *plane, t_coord center, t_coord vector)
{
    plane->vector = vector;
    normalize(&vector);
    plane->coord = do_op_coords(ADD, center, coord_constant_op(MULTIPLY, vector, ((t_cylinder *)(*__this_body()))->height / 2));
    plane->color = ((t_cylinder *)(*__this_body()))->color;
    plane->specular = ((t_cylinder *)(*__this_body()))->specular;
    plane->reflective = ((t_cylinder *)(*__this_body()))->reflective;
}

void    build_cylinder(char *input)
{
    char    **details;

    details = s().split(input, space_str());
    if (!*(details) || !*(details + 1) || !*(details + 2) || !*(details + 3) || \
		!*(details + 4) || !*(details + 5))
        error("Wrong number of arguments");
    build_plane(input);
    ((t_cylinder *)(*__this_body()))->diameter = ft_atod(details[3], (float)INT_MAX);
    ((t_cylinder *)(*__this_body()))->height = ft_atod(details[4], (float)INT_MAX);
    freepp((void **)details);
    build_cylinder_caps(&((t_cylinder *)(*__this_body()))->top, ((t_cylinder *)(*__this_body()))->coord, ((t_cylinder *)(*__this_body()))->vector);
    build_cylinder_caps(&((t_cylinder *)(*__this_body()))->bottom, ((t_cylinder *)(*__this_body()))->coord, coord_constant_op(MULTIPLY,((t_cylinder *)(*__this_body()))->vector, -1));
}