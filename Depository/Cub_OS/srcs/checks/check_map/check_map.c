/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:35:41 by abrun             #+#    #+#             */
/*   Updated: 2021/03/31 13:41:04 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game.h"

int			is_pos_hero(char **map)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E' ||
				map[y][x] == 'S' || map[y][x] == 'W')
				return (1);
			x++;
		}
		y++;
	}
	ft_putstr_fd("Il n'y a pas de répère pour le héro !\n", 1);
	return (0);
}

int			is_surrounded(t_map map)
{
	t_point		pt;
	t_point		middle;

	pt = get_hero(map.map);
	middle = pt;
	if (!get_pt_middle(&middle, map))
		return (0);
	if (!check_around(pt, map, middle))
		return (0);
	return (1);
}
