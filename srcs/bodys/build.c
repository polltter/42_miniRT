//
// Created by miguel on 17-04-2023.
//

#include "../../incs/miniRT.h"

int check_file(char *file_path)
{
    int fd;

    if (!s().end_with(file_path, ".rt"))
        error("Invalid file");
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        error("Invalid file");
    return (fd);
}

t_camera    *build_camera(char *input, int id)
{
    char        **details;
    t_camera    *camera;

    details = s().split(input, space_str());
    if (!details[0] || !details[1]|| !details[2]|| !details[3])
        error("Wrong number of camera inputs!\n");
    camera = ft_calloc(sizeof(t_camera));
    camera->id = id;
    camera->coord = get_coord(details[1], (float)1000000000);
    camera->vector = get_coord(details[2], 1);
    camera->fov = ft_atoi(details[3], 180);
    freepp((void **)details);
    if (camera->fov < 0)
        error("Invalid value for FOV!\n");
    m()->viewport.height = IMG_H / IMG_H;
    m()->viewport.width = 2 * tan(camera->fov / 2.0 * M_PI / 180.0);
    return (camera);
}

void    build_scene_helper(char *input)
{
    int id;

    id = get_id(input);
    if (id >= SPH)
        array(m()->bodys)->add(build(input, id));
    else if (id == AL)
    {
        if (m()->ambient)
            error("Scene can only have one ambient light!\n");
        m()->ambient = build_ambient_light(input, id);
    }
    else if (id == L)
        array(m()->lights)->add(build_light(input, id));
    else if (id == C)
    {
        if (m()->camera)
            error("Scene can only have one camera!\n");
        m()->camera = build_camera(input, id);
		m()->camera->theta = find_theta((t_coord){0, 0, 1}, m()->camera->vector);
        print_coords(m()->camera->theta);
    }
}

void check_scene(void)
{
    if (!array(m()->bodys)->size)
        error("Scene must have at least one body!\n");
    else if (!m()->ambient)
        error("Scene must have an ambient light!\n");
    else if (!m()->camera)
        error("Scene must have a camera!\n");
}

void    build_scene(char *file_path)
{
    int     fd;
    char    *input;

    fd = check_file(file_path);
    input = ft_calloc(1);
    m()->bodys = creat_array();
    m()->lights = creat_array();
    while (input)
    {
        free(input);
        input = get_next_line(fd);
        if (!s().equal(input,"\n") || !s().equal_n(input, "#", 1) || !input)
            continue ;
        build_scene_helper(input);
    }
    check_scene();
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