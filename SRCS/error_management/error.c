//
// Created by miguel on 18-04-2023.
//

#include "../../INCS/miniRT.h"

int    error(char *err)
{
    printf("%s\n", err);
    //funcao para dar clean de tudo antes de chamar o exit
    exit(0);
    return (0);
}