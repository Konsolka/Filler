/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:43:47 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 17:33:36 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"

void		del_node(t_vis **node)
{
	int		i;
	t_vis	*temp;

	i = 0;
	temp = *node;
	while (i < temp->map.hieght)
		ft_strdel(&temp->map.data[i++]);
	i = 0;
	while (i < temp->piece.hieght)
		ft_strdel(&temp->piece.data[i++]);
	free(temp);
	temp = NULL;
	*node = temp;
}

void		del_list(t_vis_lst **lst)
{
	t_vis_lst	*v;
	t_vis		*vis;

	v = *lst;
	while (v->v->prev)
		v->v = v->v->prev;
	ft_strdel(&v->name_1);
	ft_strdel(&v->name_2);
	while (v->v)
	{
		vis = v->v->next;
		del_node(&v->v);
		free(v->v);
		v->v = vis;
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

t_vis		*init_v(void)
{
	t_vis	*v;

	v = (t_vis *)malloc(sizeof(t_vis));
	v->next = NULL;
	v->prev = NULL;
	return (v);
}
