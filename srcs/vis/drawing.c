/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:53:26 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:16:43 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"

int			mlx_close(t_mlx *data)
{
	mlx_destroy_window(data->ptr, data->win);
	del_list(&data->v);
	exit(0);
}

void		put_score_and_win(int score_1, int score_2,
								t_vis_lst *v, t_mlx *mlx)
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
	if (score_1 > score_2)
		num = ft_strjoin(v->name_1, " wins!");
	else
		num = ft_strjoin(v->name_2, " wins!");
	mlx_string_put(mlx->ptr, mlx->win, (int)(WIDTH * 4 / 10),
					(int)(HIEGHT / 50), COLOR_YELLOW, num);
	ft_strdel(&num);
}

void		draw_win(t_vis_lst *v, t_mlx *mlx)
{
	t_coords	coords;
	t_coords	size;

	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp,
									&mlx->line_size, &mlx->ed);
	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HIEGHT;
	draw_square(size, coords, mlx, COLOR_AL_GRAY);
	draw_v_squares((int)(HIEGHT / 20 + 30), *v->v, mlx);
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
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp,
									&mlx->line_size, &mlx->ed);
	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HIEGHT;
	draw_square(size, coords, mlx, COLOR_AL_GRAY);
	draw_v_squares((int)(HIEGHT / 20 + 30), *v->v, mlx);
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
