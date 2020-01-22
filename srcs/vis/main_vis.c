/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:35:01 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 17:55:16 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

void	make_got(t_vis **v_main, char *line)
{
	t_vis	*v;

	v = *v_main;
	parce_move(line, &v->move);
	v->next = init_v();
	v->next->prev = v;
	v = v->next;
	*v_main = v;
}

void	read_file(int fd, t_vis **v_m, t_vis_lst **lst)
{
	t_vis	*v;
	char	*line;

	line = NULL;
	v = *v_m;
	while (get_next_line(fd, &line) > 0)
	{
		(*lst)->p1 = 'O';
		(*lst)->p2 = 'X';
		if (!ft_strncmp(line, "$$$ exec p1 ", 12))
			(*lst)->name_1 = parce_name(line);
		else if (!ft_strncmp(line, "$$$ exec p2 ", 12))
			(*lst)->name_2 = parce_name(line);
		else if (!ft_strncmp(line, "Plateau ", 8))
			parce_token(line, 4, &v->map, fd);
		else if (!ft_strncmp(line, "Piece ", 6))
			parce_token(line, 0, &v->piece, fd);
		else if (!ft_strncmp(line, "<got ", 5))
			make_got(&v, line);
		ft_strdel(&line);
	}
	*v_m = v;
}

int		main(int ac, char **av)
{
	t_vis_lst	*lst;
	t_vis		*v;
	char		*line;
	int			fd;

	fd = parce_args(ac, av);
	if (get_next_line(fd, &line) > 0)
	{
		if (!(!ft_strncmp(line, "# -------------- VM  version", 28)))
		{
			ft_strdel(&line);
			ft_putstr_err("Error in file\n");
		}
	}
	else
	{
		ft_strdel(&line);
		ft_putstr_err("file error\n");
	}
	v = init_v();
	lst = init_lst(v);
	read_file(fd, &v, &lst);
	v = v->prev;
	del_node(&v->next);
	v->next = NULL;
	close(fd);
	init_window(lst);
	return (0);
}
