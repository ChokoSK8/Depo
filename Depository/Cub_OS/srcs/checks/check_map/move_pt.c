/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:40:45 by abrun             #+#    #+#             */
/*   Updated: 2021/03/31 14:58:00 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game.h"

int			move_to_middle(t_point *pt, t_map map, t_moves *dir)
{
	if (dir->down && go_down(*pt, map.map, map.max_width, map.height))
	{
		printf("down\n");
		config_down(pt, dir);
	}
	else if (dir->left && go_left(*pt, map.map, map.max_width, map.height))
	{
		printf("left\n");
		config_left(pt, dir);
	}
	else if (dir->right && go_right(*pt, map.map, map.max_width, map.height))
	{
		printf("right\n");
		config_right(pt, dir);
	}
	else if (dir->up && go_up(*pt, map.map, map.max_width, map.height))
	{
		printf("up\n");
		config_up(pt, dir);
	}
	else
		return (0);
	return (1);
}

int			move_to_start(t_point *pt, t_map map, t_moves *dir)
{
	if (dir->left && go_left(*pt, map.map, map.max_width, map.height))
	{
		config_left(pt, dir);
	}
	else if (dir->down && go_down(*pt, map.map, map.max_width, map.height))
	{
		config_down(pt, dir);
	}
	else if (dir->up && go_up(*pt, map.map, map.max_width, map.height))
	{
		config_up(pt, dir);
	}
	else if (dir->right && go_right(*pt, map.map, map.max_width, map.height))
	{
		config_right(pt, dir);
	}
	else
		return (0);
	return (1);
}

int			go_left(t_point pt, char **map, int max_w, int hei)
{
	pt.x -= 1;
	if (pt.x >= 0 && map[pt.y][pt.x] == '1')
		if (is_0_around(pt, map, max_w, hei))
			return (1);
	return (0);
}

int			go_down(t_point pt, char **map, int max_w, int hei)
{
	pt.y += 1;
	if (pt.y < hei && map[pt.y][pt.x] == '1')
		if (is_0_around(pt, map, max_w, hei))
			return (1);
	return (0);
}

int			go_right(t_point pt, char **map, int max_w, int hei)
{
	pt.x += 1;
	if (pt.x < max_w && map[pt.y][pt.x] == '1')
		if (is_0_around(pt, map, max_w, hei))
			return (1);
	return (0);
}

int			go_up(t_point pt, char **map, int max_w, int hei)
{
	pt.y -= 1;
	if (pt.y >= 0 && map[pt.y][pt.x] == '1')
		if (is_0_around(pt, map, max_w, hei))
			return (1);
	return (0);
}
