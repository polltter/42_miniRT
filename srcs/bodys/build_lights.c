//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

t_ambient_light *build_ambient_light(char *input, int id)
{
    t_ambient_light *new;
    char            **details;

    details = s().split(input, space_str());
    if (!*details || !details[0] || !details[2])
        error("Wrong number of inputs for ambient light\n");
    new = ft_calloc(sizeof(t_ambient_light));
    new->id = id;
    new->light_ratio = ft_atod(details[1], 1.0);
    new->color = get_color(details[2]);
    freepp((void **)details);
    return (new);
}

void    *build_light(char *input, int id)
{
    t_light *new;
    char            **details;

    new = ft_calloc(sizeof(t_light));
    details = s().split(input, space_str());
    if (!*details || !details[0] || !details[2] || !details[3])
        error("Wrong number of inputs for light point");
    new->id = id;
    new->light_ratio = ft_atod(details[1], 1.0);
    new->coord = get_coord(details[2], (float)(1000000000));
    new->color = get_color(details[3]);
    freepp((void **)details);
    return (new);
}
