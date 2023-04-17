/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:19:24 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/14 21:34:04 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

t_array	**__this(void);

void	**__to_array(void)
{
	void	**arr;
	t_elems	*temp;
	int		i;

	arr = ft_calloc(((*__this())->size + 1) * sizeof(void *));
	temp = (*__this())->begin;
	i = 0;
	while (temp)
	{
		arr[i++] = temp->cont;
		temp = temp->next;
	}
	return (arr);
}

t_tree	*find_leaf(t_tree *temp, void *cont, int (*cmp)(void *cont1,
			void *cont2))
{
	t_tree	*leaf;
	int		val;

	val = cmp(temp->cont, cont);
	leaf = NULL;
	if (val < 0 && temp->right)
		leaf = find_leaf(temp->right, cont, cmp);
	else if (val < 0 && !temp->right)
		return (temp);
	else if (val > 0 && temp->left)
		leaf = find_leaf(temp->left, cont, cmp);
	else
		return (temp);
	return (leaf);
}

t_tree	*__add_leaf(void *cont)
{
	t_tree	*new;
	t_tree	*temp;

	new = ft_calloc(sizeof(t_tree));
	new->cont = cont;
	if (!(*__this())->root)
		(*__this())->root = new;
	else
	{
		temp = find_leaf((*__this())->root, cont, (*__this())->cmp);
		if ((*__this())->cmp(temp->cont, cont) <= 0)
			temp->right = new;
		else
			temp->left = new;
		new->up = temp;
	}
	return (new);
}

void	__build_tree(void)
{
	t_elems	*temp;

	temp = (*__this())->begin;
	if ((*__this())->root)
		return ;
	while (temp)
	{
		(*__this())->add_leaf(temp->cont);
		temp = temp->next;
	}
}

t_tree	*__search_tree(t_tree *root, void *cont)
{
	t_tree	*elem;
	int		val;

	elem = NULL;
	if (!cont)
		return (NULL);
	if (!root)
		root = (*__this())->root;
	if (!root)
		return (NULL);
	val = (*__this())->cmp(root->cont, cont);
	if (val < 0 && root->right)
		elem = __search_tree(root->right, cont);
	else if (val > 0 && root->left)
		elem = __search_tree(root->left, cont);
	else if (val == 0)
		elem = root;
	return (elem);
}
