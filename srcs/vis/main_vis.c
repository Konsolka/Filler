/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:35:01 by mburl             #+#    #+#             */
/*   Updated: 2020/01/20 18:01:09 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"
#include "get_next_line.h"

int		main(void)
{
	char		*line;
	char		*name;
	t_vis_lst	*lst;
	t_vis		*v;

	line = NULL;
	lst = NULL;
	v = (t_vis *)malloc(sizeof(t_vis));
	while (get_next_line(0, &line))
	{
		if (!ft_strncmp(line, "$$$ exec p1", 11))
		{
			v->p1 = 'O';
			v->name_1 = parce_name(line);
		}
		else if (!ft_strncmp(line, "$$$ exec p2", 11))
		{
			v->p2 = 'X';
			v->name_2 = parce_name(line);
		}
		else if (!ft_strncmp(line, "Plateau ", 8))
			parce_token(line, 4, &v->map);
		else if (!ft_strncmp(line, "Piece ", 6))
			parce_token(line, 0, &v->piece);
		else if (!ft_strncmp(line, "<got ", 5))
		{
			parce_move(line, &v->move);
			add_node(&lst, create_node(v));
			v = (t_vis *)malloc(sizeof(t_vis));
		}
		ft_strdel(&line);
	}
	init_window(lst);
	// printf("name p1 %c = %s\nname p2 %c = %s", v.p1, v.name_1, v.p2, v.name_2);
	// printf("\nmap->hieght = %i\nmap->width = %i\npiece->hieght = %i\npiece->width = %i\nmove->h = %i\nmove->w = %i\nmove->p = %c", v.map.hieght, v.map.width, v.piece.hieght, v.piece.width, v.move.h, v.move.w, v.move.p);
	return (0);
}