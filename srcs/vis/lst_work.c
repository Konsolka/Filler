/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:43:47 by mburl             #+#    #+#             */
/*   Updated: 2020/01/20 17:52:21 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>

void		add_node(t_vis_lst **lst, t_vis_lst *node)
{
	t_vis_lst	*temp;

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

t_vis_lst	*create_node(t_vis *v)
{
	t_vis_lst	*node;

	if (!v)
		return (NULL);
	node = (t_vis_lst *)malloc(sizeof(t_vis_lst));
	node->v = v;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}