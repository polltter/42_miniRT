//
// Created by miguel on 17-04-2023.
//

#ifndef MINIRT_H
#define MINIRT_H

# include "../SRCS/list/list_utils.h"
# include "../SRCS/strs/ft_strings.h"
# include "../mlx_linux/mlx.h"
# include "structs.h"
# include "limits.h"
# include "stdio.h"
# include "math.h"

#define IMG_W 1000
#define IMG_H 1000

//bodys/build.c



//mlx_utils_0
t_mlx_data *mlx();
void	data_init(t_mlx_data *data);
int	    ft_close(t_mlx_data *data);
int	    handle_keys(int k);

//error_management/error.c
int    error(char *err);

//utils/utils.c
double	    ft_atod(char *str, double max);
int	        ft_atoi(char *nptr, int max);
void        freepp(void **to_free);


#endif
