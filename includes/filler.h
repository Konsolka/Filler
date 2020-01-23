/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:13:52 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 16:41:11 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define MAX(A, B)(A > B ? A : B)
# define MIN(A, B)(A < B ? A : B)

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

t_point			closest_pair(t_filler *f);
t_point			find_place(t_filler f);
int				try_place(t_filler f, t_point point);
int				place_around(t_filler f, t_point p, t_point *res);
void			place(t_filler f);
void			free_map(t_map *map, int offset);
void			filler_free(t_filler *f);
void			del_buf(t_filler *f);

#endif
