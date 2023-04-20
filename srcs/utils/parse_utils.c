//
// Created by miguel on 18-04-2023.
//

#include "../../incs/miniRT.h"

int	ft_atoi(char *nptr, int max)
{
    int	sign;
    int	i;
    int	nb;

    nb = 0;
    i = 0;
    sign = 1;
    while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
        i++;
    if (nptr[i] == '+' || nptr[i] == '-')
    {
        if (nptr[i] == '-')
            sign *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        nb *= 10;
        nb += nptr[i] - '0';
        i++;
        if (nb > max)
        {
            printf("%d\n", max);
            error("Argument to big.\n");
        }
    }
    return (sign * nb);
}

double	ft_atod(char *str, double max)
{
    int		i;
    double	d;
    int		sign;
    int     j;

    sign = 1;
    d = 0;
    j = 0;
    printf("inside atod %f -- %d\n", max, (int)max);
    i = ft_atoi(str, ceil(max));
    if (!s().contains(str, "."))
        return (i * 1.0);
    if (*str == '-')
        sign = -1;
    while (str[j])
        j++;
    while (j && str[--j] >= '0' && str[j] <= '9')
    {
        d += str[j] - '0';
        d /= 10.0;
    }
    return (((sign * d + i) * (sign * d + i) <= max) \
        || error("Argument to big.\n"));
}

void    freepp(void **to_free)
{
    int i;

    i = -1;
    while (to_free[++i])
        free(to_free[i]);
    free(to_free);
}

int    error(char *err)
{
    exit(write(2, err, s().len(err, 0)));
}