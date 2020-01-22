/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:53:26 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 14:25:03 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"

void	draw_square(int size_x, int size_y, int x, int y, t_mlx *mlx, int long color)
{
	int			i;
	int			temp_x;
	int			temp_y;

	temp_y = y;
	while (temp_y < size_y + y && temp_y < HIEGHT)
	{
		temp_x = x;
		while (temp_x < size_x + x && temp_x < WIDTH)
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

void	draw_names(t_vis_lst v, t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, WIDTH / 4, HIEGHT / 20, COLOR_RED, v.name_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 4, HIEGHT / 20, COLOR_BLUE, v.name_2);
}

int		mlx_close(t_mlx *data)
{
	mlx_destroy_window(data->ptr, data->win);
	del_list(&data->v);
	exit(0);
}

int		key_parce(int key, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == 53)
		mlx_close(param);
	else if (key == 124)
	{
		if (data->v->v->next)
		{
			data->v->v = data->v->v->next;
			while (data->v->v->map.hieght == 0)
				data->v->v = data->v->v->next;
		}
		draw(data->v, data);
	}
	else if (key == 123)
	{
		if (data->v->v->prev)
		{
			data->v->v = data->v->v->prev;
			while (data->v->v->map.hieght == 0)
				data->v->v = data->v->v->prev;
		}
		draw(data->v, data);
	}	
	return (0);
}

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

void	calc_score(t_vis_lst *v, t_mlx *mlx)
{
	int		i;
	int		score_1;
	int		score_2;
	int		j;
	char	letter;
	char	*num;

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
	num = ft_itoa(score_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 2 / 5, HIEGHT / 20, COLOR_RED, num);
	ft_strdel(&num);
	num = ft_itoa(score_2);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 5, HIEGHT / 20, COLOR_BLUE, num);
	ft_strdel(&num);
}

void	draw_v_squares(t_vis v, t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		start_x;
	int		start_y;

	j = 1;
	if (v.map.hieght == 0)
		return ;
	x = (int)((HIEGHT - HIEGHT * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
	y = (int)((WIDTH - WIDTH * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
	start_y = HIEGHT / 20 + 30;
	while (j <= v.map.hieght)
	{
		start_x = WIDTH / 2 - ((x * v.map.width + 1 * v.map.width) / 2);
		i = 1;
		while (i <= v.map.width)
		{
			draw_square(x, y, start_x, start_y, mlx, get_square_color(i, j, v));
			i++;
			start_x += x + 1;
		}
		j++;
		start_y += y + 1;
	}
}

void	draw_move(t_vis_lst *v, t_mlx *mlx)
{
	char	*num;
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH), (int)HIEGHT * 0.7 - 20, COLOR_WHITE, "Move:");
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 55, (int)HIEGHT * 0.7 - 20, COLOR_WHITE, v->v->move.p);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 80, (int)HIEGHT * 0.7 - 20, COLOR_WHITE, "x=");
	num = ft_itoa(v->v->move.w);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 100, (int)HIEGHT * 0.7 - 20, COLOR_WHITE, num);
	ft_strdel(&num);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 80, (int)HIEGHT * 0.7 - 5, COLOR_WHITE, "y=");
	num = ft_itoa(v->v->move.h);
	mlx_string_put(mlx->ptr, mlx->win, (int)(0.2 * WIDTH) + 100, (int)HIEGHT * 0.7 - 5, COLOR_WHITE, num);
	ft_strdel(&num);

}

void	draw(t_vis_lst *v, t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	draw_square(1000, 1000, 0, 0, mlx, COLOR_AL_GRAY);
	draw_v_squares(*v->v, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img);
	calc_score(v, mlx);
	draw_move(v, mlx);
	draw_names(*v, mlx);
}

void	init_window(t_vis_lst *v)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, "Filler");
	mlx.v = v;
	draw(v, &mlx);
	mlx_key_hook(mlx.win, key_parce, &mlx);
	mlx_loop(mlx.ptr);
}