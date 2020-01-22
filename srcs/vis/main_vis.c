/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:35:01 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 14:22:58 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	char		*line;
	t_vis_lst	*lst;
	t_vis		*v;
	int			fd;

	line = NULL;
	v = init_v();
	lst = init_lst(v);
	fd = parce_args(ac, av);
	while (get_next_line(fd, &line) > 0)
	{
		lst->p1 = 'O';
		lst->p2 = 'X';
		if (!ft_strncmp(line, "$$$ exec p1 ", 12))
			lst->name_1 = parce_name(line);
		else if (!ft_strncmp(line, "$$$ exec p2 ", 12))
			lst->name_2 = parce_name(line);
		else if (!ft_strncmp(line, "Plateau ", 8))
			parce_token(line, 4, &v->map, fd);
		else if (!ft_strncmp(line, "Piece ", 6))
			parce_token(line, 0, &v->piece, fd);
		else if (!ft_strncmp(line, "<got ", 5))
		{
			parce_move(line, &v->move);
			v->next = init_v();
			v->next->prev = v;
			v = v->next;
			ft_putstr(line);
			ft_putchar('\n');
		}
		ft_strdel(&line);
	}
	if (get_next_line(fd, &line) < 0)
		ft_putstr_err("file error\n");
	v = v->prev;
	del_node(v->next);
	close(fd);
	init_window(lst);
	return (0);
}