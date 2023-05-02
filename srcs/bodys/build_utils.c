//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

t_body	*body(void *obj)
{
    *__this_body() = obj;
    return (*__this_body());
}

char    *space_str(void)
{
    return (" \t\n\v\f\r");
}

int get_color(char *color)
{
    char    **colors;
    int     r;
    int     g;
    int     b;

    colors = s().split(color, ",");
    if (!*colors || !*(colors + 1) || !*(colors + 2))
    {
        freepp((void **)colors);
        error("Wrong number of arguments for colors");
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

    coords = s().split(s_coords, ",");
    if (!*coords || !*(coords + 1) || !*(coords + 2))
        error("Wrong number of arguments");
    coord.x = ft_atod(coords[0], max);
    coord.y = ft_atod(coords[1], max);
    coord.z = ft_atod(coords[2], max);
    freepp((void **)coords);
    return (coord);
}

int clean_id(char **s_id)
{
    freepp((void **)s_id);
    return (1);
}

int get_id(char *input)
{
    char    **s_id;

    s_id = s().split(input, space_str());
    if (!*s_id)
        error("Wrong number of inputs");
    if (!s().equal(*s_id, "sp") && clean_id(s_id))
        return (SPH);
    else if (!s().equal(*s_id, "pl") && clean_id(s_id))
        return (PL);
    else if (!s().equal(*s_id, "cy") && clean_id(s_id))
        return (CY);
    else if (!s().equal(*s_id, "A") && clean_id(s_id))
        return (AL);
    else if (!s().equal(*s_id, "L") && clean_id(s_id))
        return (L);
    else if (!s().equal(*s_id, "C") && clean_id(s_id))
        return (C);
    clean_id(s_id);
    error("Not a valid identifier!");
    return (0);
}
