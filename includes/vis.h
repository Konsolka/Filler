/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:39:12 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 16:52:53 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# define HIEGHT 1000
# define WIDTH 1000

# define COLOR_WHITE		0xFFFFFF
# define COLOR_RED			0xFF0000
# define COLOR_AL_RED		0xFFA500
# define COLOR_BLUE			0x0000FF
# define COLOR_AL_BLUE		0x00FFFF
# define COLOR_OLIVE		0xC0C0C0
# define COLOR_AL_GRAY		0x505050
# define COLOR_BLACK		0x000000
# define COLOR_YELLOW		0xFFFF00

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_player
{
	char	id;
	t_point	start;
}				t_player;

typedef struct	s_map
{
	int		width;
	int		hieght;
	int		size;
	char	**data;
}				t_map;

typedef struct	s_filler
{
	int			init;
	t_player	player;
	t_player	enemy;
	t_point		target;
	t_map		board;
	t_map		token;
	t_point		*buf_p;
	t_point		*buf_e;
	int			p_count;
	int			e_count;
}				t_filler;

typedef struct	s_coords
{
	int			x;
	int			y;
}				t_coords;

typedef struct	s_move
{
	int		h;
	int		w;
	char	p[2];
}				t_move;

typedef struct	s_vis
{
	t_map			map;
	t_map			piece;
	t_move			move;
	struct s_vis	*next;
	struct s_vis	*prev;
}				t_vis;

typedef	struct	s_vis_lst
{
	char	p1;
	char	p2;
	char	*name_1;
	char	*name_2;
	t_vis	*v;
}				t_vis_lst;

typedef	struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	int			bpp;
	int			line_size;
	int			ed;
	char		*line;
	t_vis_lst	*v;
}				t_mlx;

int				mlx_close(t_mlx *data);
int				key_parce(int key, void *param);
int long		get_square_color(int x, int y, t_vis v);
void			calc_score(t_vis_lst *v, t_mlx *mlx);
void			calc_score_win(t_vis_lst *v, t_mlx *mlx);
void			parce_token(char *line, int offset, t_map *map, int fd);
void			parce_move(char *line, t_move *move);
char			*parce_name(char *line);
void			init_window(t_vis_lst *v);
void			init_window(t_vis_lst *v);
void			add_node(t_vis **lst, t_vis *node);
t_vis_lst		*init_lst(t_vis *v);
void			draw(t_vis_lst *v, t_mlx *mlx);
t_vis			*init_v();
int				parce_args(int ac, char **av);
void			draw_v_squares(int start_y, t_vis v, t_mlx *mlx);
void			del_list(t_vis_lst **lst);
void			del_node(t_vis **node);
void			draw_win(t_vis_lst *v, t_mlx *mlx);
void			draw_names(t_vis_lst v, t_mlx *mlx);
void			draw_keys(t_mlx *mlx);
void			draw_move(t_vis_lst *v, t_mlx *mlx);
void			draw_square(t_coords size, t_coords coords,
							t_mlx *mlx, int long color);
void			put_score_and_win(int score_1, int score_2,
								t_vis_lst *v, t_mlx *mlx);
#endif
