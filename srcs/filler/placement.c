/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:51:47 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 13:51:31 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

int			pos_valid(t_filler f, t_point p)
{
	return (p.x >= 0 && p.y >= 0 &&
			p.x < f.board.width && p.y < f.board.hieght);
}

int			place_around(t_filler f, t_point p, t_point *res)
{
	t_point		offset;

	offset.y = 0;
	while (offset.y < f.token.hieght)
	{
		offset.x = 0;
		while (offset.x < f.token.width)
		{
			res->x = p.x - offset.x;
			res->y = p.y - offset.y;
			if (f.token.data[offset.y][offset.x] == '*' &&
					pos_valid(f, *res) && !try_place(f, *res))
			{
				return (1);
			}
			offset.x++;
		}
		offset.y++;
	}
	return (0);
}

void		place(t_filler f)
{
	t_point		piece;

	piece = closest_pair(&f);
	del_buf(&f);
	if (!pos_valid(f, piece))
	{
		piece.x = 0;
		piece.y = 0;
		ft_putstr("0 0\n");
		exit(0);
	}
	ft_putnbr(piece.y);
	ft_putchar(' ');
	ft_putnbr(piece.x);
	ft_putchar('\n');
}

int			try_place(t_filler f, t_point point)
{
	t_point p;
	int		count;

	if (point.y + f.token.hieght > f.board.hieght ||
			point.x + f.token.width > f.board.width)
		return (2);
	count = 0;
	p.y = 0;
	while (p.y < f.token.hieght)
	{
		p.x = 0;
		while (p.x < f.token.width)
		{
			if (f.token.data[p.y][p.x] == '*' &&
			(f.board.data[point.y + p.y][point.x + p.x] == f.enemy.id))
				return (1);
			if (f.token.data[p.y][p.x] == '*' &&
			(f.board.data[point.y + p.y][point.x + p.x] == f.player.id) &&
			++count > 1)
				return (1);
			p.x++;
		}
		p.y++;
	}
	return (count < 1 ? 1 : 0);
}

t_point		find_place(t_filler f)
{
	t_point	p;
	t_point	temp;

	p.y = f.target.y;
	while (f.target.y == 0 ? p.y < f.board.hieght : p.y >= 0)
	{
		p.x = f.target.x;
		while (f.target.x == 0 ? p.x < f.board.width : p.x >= 0)
		{
			if (f.board.data[p.y][p.x] == f.player.id &&
					place_around(f, p, &temp))
				return (temp);
			p.x += (f.target.x == 0 ? 1 : -1);
		}
		p.y += (f.target.y == 0 ? 1 : -1);
	}
	return (p);
}
