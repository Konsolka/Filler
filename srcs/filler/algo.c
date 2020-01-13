/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:05:33 by mburl             #+#    #+#             */
/*   Updated: 2020/01/10 17:45:01 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"


void			create_arr(t_filler *f)
{
	int		size;

	if (f->buf_p)
		ft_memdel((void **)&f->buf_p);
	if (f->buf_e)
		ft_memdel((void **)&f->buf_e);
	size = f->board.size;
	if (!(f->buf_p = ft_memalloc(size * sizeof(t_point))) ||
			!(f->buf_e = ft_memalloc(size * sizeof(t_point))))
		exit(1);
	ft_bzero(f->buf_p, size * sizeof(t_point));
	ft_bzero(f->buf_e, size * sizeof(t_point));
}

void			pop_arr(t_filler *f)
{
	t_point	point;

	create_arr(f);
	f->p_count = 0;
	f->e_count = 0;
	point.y = 0;
	while (point.y < f->board.hieght)
	{
		point.x = 0;
		while (point.x < f->board.width)
		{
			if (f->board.data[point.y][point.x] == f->player.id)
				f->buf_p[f->p_count++] = point;
			else if (f->board.data[point.y][point.x] == f->enemy.id)
				f->buf_e[f->e_count++] = point;
			point.x++;
		}
		point.y++;
	}
}

int		calc_dist(t_point a, t_point b)
{
	return (MAX(a.x, b.x) - MIN(a.x, b.x) + 
				MAX(a.y, b.y) - MIN(a.y, b.y));
}

t_point		closest_pair(t_filler f)
{
	int		p_cur;
	int		e_cur;
	t_point	temp;
	t_point	p;
	int		dist;

	pop_arr(&f);
	dist = f.board.size;
	p_cur = 0;
	while (p_cur < f.p_count)
	{
		e_cur = 0;
		while (e_cur < f.e_count)
		{
			if (calc_dist(f.buf_p[p_cur], f.buf_e[e_cur]) <= dist &&
					place_around(f, f.buf_p[p_cur], &temp))
			{
				p = temp;
				dist = calc_dist(f.buf_p[p_cur], f.buf_e[e_cur]);
			}
			e_cur++;
		}
		p_cur++;
	}
	return (dist == f.board.size ? find_place(f) : p);
}