/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:22:19 by mvenanci@st       #+#    #+#             */
/*   Updated: 2023/04/14 21:20:35 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

t_array		**__this(void);
void		__del_from_tree(void *cont);
void		__destroy_tree(t_tree *root);
void		__build_tree(void);

void	__del(t_elems *elem)
{
	if ((*__this())->root)
		__del_from_tree(elem->cont);
	if ((*__this())->begin == elem)
	{
		if ((*__this())->begin->next)
		{
			(*__this())->begin = (*__this())->begin->next;
			(*__this())->begin->prev = NULL;
		}
		else
			(*__this())->begin = NULL;
	}
	else if ((*__this())->begin != elem)
	{
		elem->prev->next = elem->next;
		if (elem->next)
			elem->next->prev = elem->prev;
		else
			(*__this())->end = elem->prev;
	}
	if (elem->del)
		elem->del(elem->cont);
	free(elem);
	(*__this())->size--;
}

void	__for_each(void (*func)(t_elems *elem, void *p), void *o)
{
	t_elems	*temp;

	temp = (*__this())->begin;
	while (temp)
	{
		func(temp, o);
		temp = temp->next;
	}
}

static void	default_cont_destroy(void *cont)
{
	free(cont);
}

t_elems	*__add(void *cont)
{
	t_elems	*new;

	if (!cont)
		return (NULL);
	new = ft_calloc(sizeof(t_elems));
	new->del = default_cont_destroy;
	new->cont = cont;
	if (!(*__this())->begin)
		(*__this())->begin = new;
	else
	{
		new->prev = (*__this())->end;
		(*__this())->end->next = new;
	}
	(*__this())->end = new;
	(*__this())->size++;
	if ((*__this())->root)
		(*__this())->add_leaf(cont);
	return (new);
}

void	__destroy(void)
{
	t_elems	*temp;
	t_elems	*temp2;

	if ((*__this())->root)
	{
		__destroy_tree((*__this())->root);
	}
	temp = (*__this())->begin;
	while (temp)
	{
		temp2 = temp->next;
		if (temp->del)
			temp->del(temp->cont);
		free(temp);
		temp = temp2;
	}
	free(*__this());
	*__this() = NULL;
}
