/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surrounded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:25:02 by abrun             #+#    #+#             */
/*   Updated: 2021/03/31 14:57:48 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game.h"

t_point		get_hero(char **map)
{
	t_point p;

	p.y = 0;
	while (map[p.y])
	{
		p.x = 0;
		while (map[p.y][p.x])
		{
			if (map[p.y][p.x] >= 'A' && map[p.y][p.x] <= 'Z')
				return (p);
			p.x += 1;
		}
		p.y += 1;
	}
	return (p);
}

int			get_pt_middle(t_point *pt, t_map map)
{
	int		y;
	t_moves		dir;
	int			ret;

	dir.right = 1;
	dir.left = 1;
	dir.up = 1;
	dir.down = 1;

	y = pt->y;
	while (map.map[y][pt->x] != '1')
		y++;
	pt->y = y;
	ret = 1;
	while (dir.down && ret)
		ret = move_to_start(pt, map, &dir);
	return (ret);
}

int			is_near(t_point pt, t_point target)
{
	int		i;
	int		j;

	i = target.x - 1;
	while (i <= target.x + 1)
	{
		j = target.y - 1;
		while ( j <= target.y + 1)
		{
			if (pt.x == i && pt.y == j)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			get_pt_start(t_point *pt, char **map)
{
	int			x;
	int			y;
	t_point		h;

	h = get_hero(map);
	y = h.x;
	x = h.y;
	while (map[x][y] != '1')
	{
		printf("map[%d, %d] : %c\n", x, y, map[x][y]);
		if (x <= 0)
			return (0);
		x--;
	}
	pt->x = y;
	pt->y = x;
	return (1);
}

void		get_start(t_point *pt, t_map map)
{
	int			y;
	t_point		h;

	h = get_hero(map.map);
	pt->x = h.x;
	pt->y = 0;
	y = 0;
	while (pt->y < map.height && !is_0_around(*pt, map.map, map.max_width, map.height))
		pt->y--;
}

void		print_around(t_map map, t_point pt)
{
	int		i;
	int		j;

	i = pt.y - 1;
	while (i <= pt.y + 1)
	{
		j = pt.x - 1;
		while (j <= pt.x + 1)
		{
			if (map.max_width - j >= 0 && map.height - i >= 0)
				printf("%c", map.map[i][j]);
			else
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void		print_map(t_map map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.max_width)
		{
			printf("%c", map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int			check_around(t_point pt, t_map map, t_point middle)
{
	t_moves		dir;
	int			count;
	t_point		start;

	dir.right = 1;
	dir.left = 1;
	dir.up = 1;
	dir.down = 1;
	get_start(&start, map);
	print_map(map);
	if (!get_pt_start(&pt, map.map))
		return (0);
	count = map.height * map.max_width;
	while (count > 0)
	{
		while (pt.x != middle.x || pt.y != middle.y)
		{
			if (!(move_to_middle(&pt, map, &dir)))
				return (0);
			print_around(map, pt);
			count--;
		}
		while (pt.x != start.x || pt.y != start.y)
		{
			printf("pt : (%d, %d)\n", pt.x, pt.y);
			if (!(move_to_start(&pt, map, &dir)))
				return (0);
			count--;
		}
	}
	return (1);
}
