/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:06:21 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:20:33 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void		move_right(t_mlx *data)
{
	if (data->v->v->next)
	{
		data->v->v = data->v->v->next;
		while (data->v->v->map.hieght == 0)
			data->v->v = data->v->v->next;
		draw(data->v, data);
	}
	else
		draw_win(data->v, data);
}

void		move_left(t_mlx *data)
{
	if (data->v->v->prev)
	{
		data->v->v = data->v->v->prev;
		while (data->v->v->map.hieght == 0)
			data->v->v = data->v->v->prev;
	}
	draw(data->v, data);
}

void		go_end(t_mlx *data)
{
	while (data->v->v->prev)
		data->v->v = data->v->v->prev;
	while (data->v->v->next->next)
		data->v->v = data->v->v->next;
	draw(data->v, data);
	data->v->v = data->v->v->next;
	draw_win(data->v, data);
}

int			key_parce(int key, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == 53)
		mlx_close(param);
	else if (key == 124)
		move_right(data);
	else if (key == 123)
		move_left(data);
	else if (key == 14)
		go_end(data);
	else if (key == 1)
	{
		while (data->v->v->prev)
			data->v->v = data->v->v->prev;
		draw(data->v, data);
	}
	return (0);
}
