/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:41:19 by mburl             #+#    #+#             */
/*   Updated: 2020/01/13 17:44:05 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_map(t_map *map)
{
	int		i;
	char	*str;

	if (!map->data)
		return ;
	i = 0;
	while (i < map->hieght)
	{
		ft_strdel(&map->data[i]);
		i++;
	}
	ft_memdel((void **)map->data);
}

void	read_map(char *line, int offset, t_map *map)
{
	int		i;

	free_map(map);
	line = ft_strchr(line, ' ') + 1;
	map->hieght = ft_atoi(line);
	map->width = ft_atoi(ft_strchr(line, ' '));
	map->size = map->hieght * map->width;
	if (offset)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	map->data = (char **)malloc(sizeof(char *) * map->hieght);
	i = 0;
	while (i < map->hieght)
	{
		get_next_line(0, &line);
		map->data[i] = ft_strdup(line + offset);
		ft_strdel(&line);
		i++;
	}
}

void	init_filler(t_filler *filler)
{
	t_point	p;

	p.y = 0;
	while (p.y < filler->board.hieght)
	{
		p.x = 0;
		while (p.x < filler->board.width)
		{
			if (filler->board.data[p.y][p.x] == filler->player.id)
				filler->player.start = p;
			else if (filler->board.data[p.y][p.x] == filler->enemy.id)
				filler->enemy.start = p;
			p.x++;
		}
		p.y++;
	}
	filler->target.x = (filler->enemy.start.x - filler->player.start.x < 0 ?
						0 : filler->board.width - 1);
	filler->target.y = (filler->enemy.start.y - filler->player.start.y < 0 ?
						0 : filler->board.hieght - 1);
	filler->init = 1;
}

void	filler_loop(t_filler filler)
{
	char	*str;
	int		res;

	while ((res = get_next_line(0, &str)) > -1)
	{
		if (!str)
			continue ;
		if (!ft_strncmp(str, "Plateau ", 8))
		{
			read_map(str, 4, &filler.board);
			if (!filler.init)
				init_filler(&filler);
		}
		else if (!ft_strncmp(str, "Piece ", 6))
		{
			read_map(str, 0, &filler.token);
			place(filler);
		}
		if (str)
			ft_strdel(&str);
	}
}

int			main(void)
{
	t_filler	filler;
	char		*line;

	ft_bzero(&filler, sizeof(t_filler));
	line = NULL;
	filler.init = 0;
	if (get_next_line(0, &line) && line && ft_strlen(line) > 10 &&
			!ft_strncmp(line, "$$$ exec p", 9) &&
			(line[10] == '1' || line[10] == '2'))
	{
		filler.player.id = (line[10] == '1' ? 'O' : 'X');
		filler.enemy.id = (line[10] == '1' ? 'X' : 'O');
		ft_strdel(&line);
		filler_loop(filler);
	}
	else
		return (1);
	return (0);
}