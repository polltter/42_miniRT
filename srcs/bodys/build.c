//
// Created by miguel on 17-04-2023.
//

#include "../../incs/miniRT.h"

//void    build_scene(char *file_path)
//{
//    int     id;
//    int     fd;
//    char    **details;
//    char    *input;
//
//    fd = open(file_path, O_RDONLY);
//    if (fd < 0)
//        error("Invalid file");
//    input = get_next_line(fd);
//    m()->bodys = creat_array();
//    m()->lights = creat_array();
//    while (input)
//    {
//        details = s().split(input, space_str());
//        id = get_id(*details);
//
//        freepp((void **)details);
//    }
//
//
//}

void    *build(char *input, int id)
{
    void    *b;


    b = NULL;
    if (id == PL)
    {
        b = ft_calloc(sizeof(t_plane));
        body(b);
        build_plane(input);
    }
    else if (id == SPH)
    {
        b = ft_calloc(sizeof(t_sphere));
        body(b);
        build_sphere(input);
    }
    else if (id == CY)
    {
        b = ft_calloc(sizeof(t_cylinder));
        body(b);
        build_cylinder(input);
    }
    else
        error("Wrong identifier.");
    return (b);
}