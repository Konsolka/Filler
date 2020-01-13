/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:35:01 by mburl             #+#    #+#             */
/*   Updated: 2020/01/13 18:43:12 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
int		main(void)
{
	char	*line;
	char	*temp;
	char	**temp_split;
	t_vis	v;
	int		offset;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (!ft_strncmp(line, "$$$ exec p1", 11))
		{
			v.p1 = 'O';
			v.name_1 = parce_name(line);
		}
		else if (!ft_strncmp(line, "$$$ exec p2", 11))
		{
			v.p2 = 'X';
			v.name_2 = parce_name(line);
		}
		ft_strdel(&line);
	}
	printf("name p1 %c = %s\nname p2 %c = %s", v.p1, v.name_1, v.p2, v.name_2);
	return (0);
}