/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:53:26 by mburl             #+#    #+#             */
/*   Updated: 2020/01/20 18:08:56 by mburl            ###   ########.fr       */
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

void	draw_names(t_vis v, t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, WIDTH / 4, HIEGHT / 20, COLOR_RED, v.name_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 4, HIEGHT / 20, COLOR_BLUE, v.name_2);
}

int		mlx_close(t_mlx *data)
{
	mlx_destroy_window(data->ptr, data->win);
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
		if (data->v->next)
			data->v = data->v->next;
		draw(*data->v->v, data);
	}
	else if (key == 123)
	{
		if (data->v->prev)
			data->v = data->v->prev;
		draw(*data->v->v, data);
	}
	return (0);
}

int long	get_square_color(int x, int y, t_vis v, t_mlx *mlx)
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

void	calc_score(t_vis v, t_mlx *mlx)
{
	int		i;
	int		j;
	int		score_p1;
	int		score_p2;
	char	letter;

	score_p1 = 0;
	score_p2 = 0;
	j = 0;
	while (j < v.map.hieght)
	{
		i = 0;
		while (i < v.map.width)
		{
			letter = v.map.data[j][i];
			if (letter == 'O')
				score_p1++;
			else if (letter == 'X')
				score_p2++;
			i++;
		}
		j++;
	}
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 2 / 5, HIEGHT / 20, COLOR_RED, ft_itoa(score_p1));
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 5, HIEGHT / 20, COLOR_BLUE, ft_itoa(score_p2));
}

void	draw_v_squares(t_vis v, t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		start_x;
	int		start_y;
	int		temp;

	j = 1;
	x = (int)((HIEGHT - HIEGHT * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
	y = (int)((WIDTH - WIDTH * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
	start_y = HIEGHT / 20 + 30;
	while (j <= v.map.hieght)
	{
		start_x = WIDTH / 2 - ((x * v.map.width + 1 * v.map.width) / 2);
		i = 1;
		while (i <= v.map.width)
		{
			draw_square(x, y, start_x, start_y, mlx, get_square_color(i, j, v, mlx));
			i++;
			start_x += x + 1;
		}
		j++;
		start_y += y + 1;
	}
}

void	draw(t_vis v, t_mlx *mlx)
{
		int	i = 0;
	while (i < v.map.hieght)
	{
		ft_putstr(v.map.data[i]);
		ft_putchar('\n');
		i++;
	}
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	draw_square(1000, 1000, 0, 0, mlx, COLOR_AL_GRAY);
	draw_v_squares(v, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	if (v.name_1)
		draw_names(v, mlx);
	calc_score(v, mlx);
	mlx_destroy_image(mlx->ptr, mlx->img);
}

void	init_window(t_vis_lst *v)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, "Filler");
	mlx.v = v;
	draw(*mlx.v->v, &mlx);
	mlx_key_hook(mlx.win, key_parce, &mlx);
	mlx_loop(mlx.ptr);
}