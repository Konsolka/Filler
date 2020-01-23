/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:16:10 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:22:59 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "filler.h"
#include "libft.h"

int long	get_square_color(int x, int y, t_vis v)
{
	char	letter;

	letter = v.map.data[y - 1][x - 1];
	if (letter == 'o')
		return (COLOR_AL_RED);
	else if (letter == 'O')
		return (COLOR_RED);
	else if (letter == 'x')
		return (COLOR_AL_BLUE);
	else if (letter == 'X')
		return (COLOR_BLUE);
	return (COLOR_WHITE);
}

void		put_score_string(int score_1, int score_2, t_mlx *mlx)
{
	char	*num;

	num = ft_itoa(score_1);
	mlx_string_put(mlx->ptr, mlx->win, (int)(WIDTH * 2 / 5),
					(int)(HIEGHT / 20), COLOR_RED, num);
	ft_strdel(&num);
	num = ft_itoa(score_2);
	mlx_string_put(mlx->ptr, mlx->win, (int)(WIDTH * 3 / 5),
					(int)(HIEGHT / 20), COLOR_BLUE, num);
	ft_strdel(&num);
}

void		calc_score(t_vis_lst *v, t_mlx *mlx)
{
	int		i;
	int		score_1;
	int		score_2;
	int		j;

	j = 0;
	score_1 = 0;
	score_2 = 0;
	while (j < v->v->map.hieght)
	{
		i = 0;
		while (i < v->v->map.width)
		{
			if (v->v->map.data[j][i] == v->p1 + 32 ||
					v->v->map.data[j][i] == v->p1)
				score_1++;
			else if (v->v->map.data[j][i] == v->p2 + 32 ||
						v->v->map.data[j][i] == v->p2)
				score_2++;
			i++;
		}
		j++;
	}
	put_score_string(score_1, score_2, mlx);
}

void		calc_score_win(t_vis_lst *v, t_mlx *mlx)
{
	int		i;
	int		score_1;
	int		score_2;
	int		j;
	char	letter;

	j = 0;
	score_1 = 0;
	score_2 = 0;
	while (j < v->v->map.hieght)
	{
		i = 0;
		while (i < v->v->map.width)
		{
			letter = v->v->map.data[j][i];
			if (letter == v->p1 + 32 || letter == v->p1)
				score_1++;
			else if (letter == v->p2 + 32 || letter == v->p2)
				score_2++;
			i++;
		}
		j++;
	}
	put_score_and_win(score_1, score_2, v, mlx);
}
