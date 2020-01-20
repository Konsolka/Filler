/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:39:12 by mburl             #+#    #+#             */
/*   Updated: 2020/01/20 15:07:32 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"
#include "get_next_line.h"

void	free_token(t_map *map)
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

void	parce_move(char *line, t_move *move)
{
	move->p = ft_strchr(line, '(')[1];
	move->h = ft_atoi(line);
	move->w = ft_atoi(ft_strrchr(line, ' '));
}

void	parce_token(char *line, int offset, t_map *map)
{
	int		i;

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