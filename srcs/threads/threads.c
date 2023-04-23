//
// Created by miguel on 22-04-2023.
//

#include "../../incs/miniRT.h"

void	init_threads(t_elems *elem, void *o)
{
    (void)o;
    pthread_create(&(((t_threads *)(elem->cont))->id), NULL, render, elem->cont);
}

void	join_for_each(t_elems *elem, void *o)
{
    (void)o;
    pthread_join(((t_threads *)(elem->cont))->id, NULL);
}


void	print_threads(t_elems *elem, void *o)
{
    (void)o;
    t_threads *a = (t_threads *)elem->cont;
    printf("%d--%d\n", a->strat_x, a->end_x);
}

void    imgs_to_canvas(t_elems *elem, void *o)
{
    (void)o;
    mlx_put_image_to_window(mlx()->mlx, mlx()->mlx_win, ((t_threads *)elem->cont)->img.img, ((t_threads *)elem->cont)->strat_x + IMG_W / 2, 0);

}

void    build_threads(void)
{
    int i;
    t_threads   *new;

    i = 0;
    m()->threads = creat_array();
    while (i < N_THREADS)
    {
        new = ft_calloc(sizeof(t_threads));
        new->id = i;
        new->strat_x = i * IMG_W / N_THREADS - IMG_W / 2;
        new->end_x = (i + 1) * IMG_W/ N_THREADS - IMG_W / 2;
        new->img.img = mlx_new_image(mlx()->mlx, new->end_x - new->strat_x, IMG_H);
        new->img.addr = mlx_get_data_addr(new->img.img, \
        &new->img.bits_per_pixel, &new->img.line_length, &new->img.endian);
        array(m()->threads)->add(new);
        i++;
    }

}