//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

t_default_body	*body(void *obj)
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

    coords = s().split(s_coords, ",");
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
