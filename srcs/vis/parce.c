/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:39:12 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:29:27 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>

int		parce_args(int ac, char **av)
{
	int		fd;

	fd = 0;
	if (ac == 1)
		return (fd);
	else if (ac == 3)
	{
		if (!(!ft_strcmp(av[1], "-f") || !ft_strcmp(av[1], "--file")))
			ft_putstr_err("Usage:\t| ./vis\n\t./vis [-f/--file/] file_name\n");
		if ((fd = open(av[2], O_RDONLY)) == -1)
			ft_putstr_err("file error\n");
		return (fd);
	}
	ft_putstr_err("Usage:\t| ./vis\n\t./vis [-f/--file/] file_name\n");
	return (fd);
}

void	free_token(t_map *map)
{
	int		i;

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

void	parce_move(char *line, t_move *move)
{
	move->p[0] = ft_strchr(line, '(')[1];
	move->p[1] = '\0';
	move->h = ft_atoi(ft_strchr(line, '[') + 1);
	move->w = ft_atoi(ft_strrchr(line, ' '));
}

void	parce_token(char *line, int offset, t_map *map, int fd)
{
	int		i;

	line = ft_strchr(line, ' ') + 1;
	map->hieght = ft_atoi(line);
	map->width = ft_atoi(ft_strchr(line, ' '));
	map->size = map->hieght * map->width;
	if (offset)
	{
		get_next_line(fd, &line);
		ft_strdel(&line);
	}
	map->data = (char **)malloc(sizeof(char *) * map->hieght);
	i = 0;
	while (i < map->hieght)
	{
		get_next_line(fd, &line);
		map->data[i] = ft_strdup(line + offset);
		ft_strdel(&line);
		i++;
	}
}

char	*parce_name(char *line)
{
	char	*temp;
	char	**temp_split;

	temp = ft_strrchr(line, '/') + 1;
	temp_split = ft_strsplit(temp, '.');
	temp = ft_strdup(*temp_split);
	ft_strtab_free(temp_split);
	return (temp);
}
