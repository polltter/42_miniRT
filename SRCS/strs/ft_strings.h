/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:12:40 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:55:57 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include "../list/list_utils.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_s
{
	int		(*len)(const char *, char c);
	char	*(*copy)(const char *);
	char	*(*copy_n)(const char *, int size);
	char	**(*split)(const char *, int);
	int		(*equal)(const char *, const char *);
	int		(*equal_n)(const char *, const char *, int);
	int		(*contains)(const char *, const char *);
	char	*(*trim)(const char *);
	char	*(*join)(char *, char *, char *);
	int		(*alnum)(char *);
	char	*(*append)(char *s, char c);
}			t_s;

t_s	s(void);

#endif