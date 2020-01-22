/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:53:26 by mburl             #+#    #+#             */
/*   Updated: 2020/01/22 18:41:56 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"

void		draw_square(t_coords size, t_coords coords, t_mlx *mlx, int long color)
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
	mlx_string_put(mlx->ptr, mlx->win, WIDTH / 4, HIEGHT / 20, COLOR_RED, v.name_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 4, HIEGHT / 20, COLOR_BLUE, v.name_2);
}

int			mlx_close(t_mlx *data)
{
	mlx_destroy_window(data->ptr, data->win);
	del_list(&data->v);
	exit(0);
}

int			key_parce(int key, void *param)
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
			draw(data->v, data);
		}
		else
			draw_win(data->v, data);
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
	else if (key == 14)
	{
		while (data->v->v->prev)
			data->v->v = data->v->v->prev;
		while (data->v->v->next->next)
			data->v->v = data->v->v->next;
		draw(data->v, data);
		data->v->v = data->v->v->next;
		draw_win(data->v, data);
	}
	else if (key == 1)
	{
		while (data->v->v->prev)
			data->v->v = data->v->v->prev;
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

void		calc_score(t_vis_lst *v, t_mlx *mlx)
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

void		draw_v_squares(int start_y, t_vis v, t_mlx *mlx)
{
	int		i;
	int		j;
	t_coords	coords;
	t_coords	size;

	j = 1;
	size.x = (int)((HIEGHT - HIEGHT * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
	size.y = (int)((WIDTH - WIDTH * 3 / 10) / ((v.map.width > v.map.hieght) ? v.map.width : v.map.hieght)) - 5;
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

void		draw_move(t_vis_lst *v, t_mlx *mlx)
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

void		put_score_and_win(int score_1, int score_2, t_vis_lst *v, t_mlx *mlx)
{
	char	*num;

	num = ft_itoa(score_1);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 2 / 5, HIEGHT / 20, COLOR_RED, num);
	ft_strdel(&num);
	num = ft_itoa(score_2);
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 3 / 5, HIEGHT / 20, COLOR_BLUE, num);
	ft_strdel(&num);
	if (score_1 > score_2)
		num = ft_strjoin(v->name_1, " wins!");
	else
		num = ft_strjoin(v->name_2, " wins!");
	mlx_string_put(mlx->ptr, mlx->win, WIDTH * 4 / 10, HIEGHT / 50, COLOR_YELLOW, num);
	ft_strdel(&num);
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

void		draw_keys(t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, 5, HIEGHT / 50, COLOR_YELLOW, "s - Go to begin");
	mlx_string_put(mlx->ptr, mlx->win, 5, HIEGHT / 50 + 25, COLOR_YELLOW, "e - Go to end");
	mlx_string_put(mlx->ptr, mlx->win, 5, HIEGHT / 50 + 50, COLOR_YELLOW, "esc - Exit");
	mlx_string_put(mlx->ptr, mlx->win, 5, HIEGHT / 50 + 75, COLOR_YELLOW, "-> - Next move");
	mlx_string_put(mlx->ptr, mlx->win, 5, HIEGHT / 50 + 100, COLOR_YELLOW, "<- - Previous move");
}

void		draw_win(t_vis_lst *v, t_mlx *mlx)
{
	t_coords	coords;
	t_coords	size;

	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HIEGHT;
	draw_square(size, coords, mlx, COLOR_AL_GRAY);
	draw_v_squares(HIEGHT / 20 + 30, *v->v, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img);
	calc_score_win(v, mlx);
	draw_move(v, mlx);
	draw_names(*v, mlx);
	draw_keys(mlx);
}

void		draw(t_vis_lst *v, t_mlx *mlx)
{
	t_coords	coords;
	t_coords	size;

	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HIEGHT;
	draw_square(size, coords, mlx, COLOR_AL_GRAY);
	draw_v_squares(HIEGHT / 20 + 30, *v->v, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img);
	calc_score(v, mlx);
	draw_move(v, mlx);
	draw_names(*v, mlx);
	draw_keys(mlx);
}

void		init_window(t_vis_lst *v)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, "Filler");
	mlx.v = v;
	draw(v, &mlx);
	mlx_hook(mlx.win, 2, 0, key_parce, &mlx);
	mlx_hook(mlx.win, 17, 0, mlx_close, &mlx);
	mlx_loop(mlx.ptr);
}
