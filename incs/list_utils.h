/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:03:30 by mvenanci@st       #+#    #+#             */
/*   Updated: 2023/04/06 18:49:49 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_UTILS_H
# define LIST_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_elems	t_elems;
typedef struct s_tree	t_tree;
typedef struct s_array	t_array;

struct					s_elems
{
	void				*cont;
	void				(*del)(void *cont);
	t_elems				*next;
	t_elems				*prev;
};

struct					s_tree
{
	void				*cont;
	void				(*del)(void *cont);
	t_tree				*left;
	t_tree				*right;
	t_tree				*up;
};

struct					s_array
{
	t_elems				*begin;
	t_elems				*end;
	int					size;
	t_elems				*(*add)(void *cont);
	void				(*remove)(t_elems *elem_to_del);
	void				(*for_each)(void (*func)(t_elems *elem, void *o), \
							void *o);
	void				(*destroy)(void);
	t_elems				*(*search)(int (*cmp)(void *cont, void *buf), \
							void *buf);
	void				**(*to_array)(void);
	void				(*destroy_array)(void);
	t_tree				*root;
	void				(*build_tree)(void);
	t_tree				*(*add_leaf)(void *cont);
	t_tree				*(*search_tree)(t_tree *root, void *cont);
	int					(*cmp)(void *cont1, void *cont2);
};

t_array					*array(void *lst);
void					*ft_calloc(size_t size);
void					*creat_array(void);

#endif