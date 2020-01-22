/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:43:47 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 13:41:47 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"

void		del_node(t_vis *node)
{
	int		i;
	i = 0;
	while (i < node->map.hieght)
		ft_strdel(&node->map.data[i++]);
	i = 0;
	while (i < node->piece.hieght)
		ft_strdel(&node->piece.data[i++]);
	node = NULL;
}

void		del_list(t_vis_lst **lst)
{
	t_vis_lst	*v;
	int			i;

	v = *lst;
	while (v->v->prev)
		v->v = v->v->prev;
	ft_strdel(&v->name_1);
	ft_strdel(&v->name_2);
	while (v->v)
	{
		i = 0;
		while (i < v->v->map.hieght)
			ft_strdel(&v->v->map.data[i++]);
		i = 0;
		while (i < v->v->piece.hieght)
			ft_strdel(&v->v->piece.data[i++]);
		v->v = v->v->next;
		if (!v->v)
			break ;
		free(v->v->prev);
		v->v->prev = NULL;
	}
	free(v);
	*lst = v;
}

t_vis_lst	*init_lst(t_vis *v)
{
	t_vis_lst	*lst;

	lst = (t_vis_lst *)malloc(sizeof(t_vis_lst));
	lst->v = v;
	return (lst);
}

void		add_node(t_vis **lst, t_vis *node)
{
	t_vis	*temp;

	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	node->prev = temp;
	temp->next = node;
	while (temp->prev)
		temp = temp->prev;
	*lst = temp;
}

t_vis	*init_v()
{
	t_vis	*v;

	v = (t_vis *)malloc(sizeof(t_vis));
	v->next = NULL;
	v->prev = NULL;
	return (v);
}