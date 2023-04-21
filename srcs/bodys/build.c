//
// Created by miguel on 17-04-2023.
//

#include "../../incs/miniRT.h"

int check_file(char *file_path)
{
    int fd;

    if (!s().contains(file_path, ".rt"))
        error("Invalid file");
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        error("Invalid file");
    return (fd);
}

void    build_scene(char *file_path)
{
    int     id;
    int     fd;
    char    *input;

    fd = check_file(file_path);
    input = get_next_line(fd);
    m()->bodys = creat_array();
    m()->lights = creat_array();
    while (input)
    {
        id = get_id(input);
        printf("%s\n", input);
        if (id >= SPH)
            array(m()->bodys)->add(build(input, id));
        else if (id == AL)
            m()->ambient = build_AL(input, id);
        else if (id == L)
            array(m()->lights)->add(build_light(input, id));
        free(input);
        input = get_next_line(fd);
    }
    free(input);
}


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