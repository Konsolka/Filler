/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:12:23 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 16:44:30 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "vis.h"

void		draw_move(t_vis_lst *v, t_mlx *mlx)
{
	char	*num;

	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH),
					(int)HIEGHT * 0.7 - 20, COLOR_WHITE, "Move:");
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 55,
					(int)HIEGHT * 0.7 - 20, COLOR_WHITE, v->v->move.p);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 80,
					(int)HIEGHT * 0.7 - 20, COLOR_WHITE, "x=");
	num = ft_itoa(v->v->move.w);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 100,
					(int)HIEGHT * 0.7 - 20, COLOR_WHITE, num);
	ft_strdel(&num);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 80,
					(int)HIEGHT * 0.7 - 5, COLOR_WHITE, "y=");
	num = ft_itoa(v->v->move.h);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 100,
					(int)HIEGHT * 0.7 - 5, COLOR_WHITE, num);
	ft_strdel(&num);
}

void		draw_square(t_coords size, t_coords coords,
							t_mlx *mlx, int long color)
{
	int			i;
	int			temp_x;
	int			temp_y;

	temp_y = coords.y;
	while (temp_y < size.y + coords.y && temp_y < HIEGHT)
	{
		temp_x = coords.x;
		while (temp_x < size.y + coords.x && temp_x < WIDTH)
		{
			i = (temp_x * mlx->bpp / 8) + (temp_y * mlx->line_size);
			mlx->line[i] = color;
			mlx->line[++i] = color >> 8;
			mlx->line[++i] = color >> 16;
			temp_x++;
		}
		temp_y++;
	}
}

void		draw_names(t_vis_lst v, t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, (int)(WIDTH / 4),
					(int)(HIEGHT / 20), COLOR_RED, v.name_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 4,
					(int)(HIEGHT / 20), COLOR_BLUE, v.name_2);
}

void		draw_keys(t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, 5, (int)(HIEGHT / 50),
						COLOR_YELLOW, "s - Go to begin");
	mlx_string_put(mlx->ptr, mlx->win, 5, (int)(HIEGHT / 50 + 25),
						COLOR_YELLOW, "e - Go to end");
	mlx_string_put(mlx->ptr, mlx->win, 5, (int)(HIEGHT / 50 + 50),
						COLOR_YELLOW, "esc - Exit");
	mlx_string_put(mlx->ptr, mlx->win, 5, (int)(HIEGHT / 50 + 75),
						COLOR_YELLOW, "-> - Next move");
	mlx_string_put(mlx->ptr, mlx->win, 5, (int)(HIEGHT / 50 + 100),
						COLOR_YELLOW, "<- - Previous move");
}

void		draw_v_squares(int start_y, t_vis v, t_mlx *mlx)
{
	int			i;
	int			j;
	t_coords	coords;
	t_coords	size;

	j = 1;
	size.x = (int)((HIEGHT - HIEGHT * 3 / 10) / ((v.map.width > v.map.hieght)
				? v.map.width : v.map.hieght)) - 5;
	size.y = (int)((WIDTH - WIDTH * 3 / 10) / ((v.map.width > v.map.hieght)
				? v.map.width : v.map.hieght)) - 5;
	coords.y = start_y;
	while (j <= v.map.hieght)
	{
		coords.x = WIDTH / 2 - ((size.x * v.map.width + 1 * v.map.width) / 2);
		i = 1;
		while (i <= v.map.width)
		{
			draw_square(size, coords, mlx, get_square_color(i, j, v));
			i++;
			coords.x += size.x + 1;
		}
		j++;
		coords.y += size.y + 1;
	}
}
