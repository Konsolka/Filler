/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:39:12 by mburl             #+#    #+#             */
/*   Updated: 2020/01/13 18:43:51 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*parce_name(char *line)
{
	char	*temp;
	char	**temp_split;

	temp = ft_strrchr(line, '/') + 1;
	temp_split = ft_strsplit(temp, '.');
	temp = ft_strdup(*temp_split);
	ft_strtab_free(temp_split);
	return (temp);
}