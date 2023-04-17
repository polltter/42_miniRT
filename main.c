#include "INCS/miniRT.h"

t_mlx_data *mlx(){

    static t_mlx_data data;

    return (&data);
}

void	data_init(t_mlx_data *data)
{
    data->mlx = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx, IMG_W, IMG_H, "MiniRT");
    data->img.img = mlx_new_image(data->mlx, IMG_W, IMG_H);
    data->img.addr = mlx_get_data_addr(data->img.img, \
	&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

int	ft_close(t_mlx_data *data)
{
    mlx_destroy_image(data->mlx, data->img.img);
    mlx_destroy_window(data->mlx, data->mlx_win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
}

int	handle_keys(int k)
{
    if (k == 65307)
        ft_close(mlx());
    return (1);
}

int main() {

    t_mlx_data data;
    data_init(&data);
    *mlx() = data;
    mlx_hook(data.mlx_win, 17, 0, ft_close, &data);
    mlx_hook(mlx()->mlx_win, 2, 1l << 0, handle_keys, NULL);
    mlx_loop(data.mlx);
    return 0;
}
