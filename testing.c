//
// Created by miguel on 18-04-2023.
//

#include "INCS/miniRT.h"

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
            error("Argument to big\n");
        }
    }
    return (sign * nb);
}

double	ft_atod(char *str)
{
    int		i;
    double	d;
    int		sign;
    int     j;

    sign = 1;
    d = 0;
    j = 0;
    i = ft_atoi(str, INT_MAX);
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
    return (sign * d + i);
}

int main(void)
{
    printf("%f\n", ft_atod("5.5"));
    printf("%f\n", ft_atod("-5.5"));
    printf("%f\n", ft_atod("-1"));
    printf("%f\n", ft_atod("-0.5"));
    printf("%f\n", ft_atod("10000"));
}
