/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_vert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:11:52 by abrun             #+#    #+#             */
/*   Updated: 2021/03/18 15:30:31 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

void		get_pt_a_vert(t_player hero, t_vect *pt_a, t_map map, double angle)
{
	if (angle > 180)
	{
		pt_a->x = hero.vec.x + map.len_pix - modulo(hero.vec.x, map.len_pix);
		if (pt_a->x == hero.vec.x)
			pt_a->x += map.len_pix;
		if (angle > 270)
			pt_a->y = hero.vec.y - tan(convert(angle - 270)) * (pt_a->x - hero.vec.x);
		else
			pt_a->y = hero.vec.y + tan(convert(270 - angle)) * (pt_a->x - hero.vec.x);
	}
	else
	{
		pt_a->x = hero.vec.x - modulo(hero.vec.x, map.len_pix);
		if (pt_a->x == hero.vec.x)
			pt_a->x -= map.len_pix;
		if (angle < 90)
			pt_a->y = hero.vec.y - tan(convert(angle + 90)) * (pt_a->x - hero.vec.x);
		else
			pt_a->y = hero.vec.y - tan(convert(angle - 90)) * (pt_a->x - hero.vec.x);
	}
}

void		get_pt_a_vert_90(t_player hero, t_vect *pt_a,
		t_map map, double angle)
{
	pt_a->y = hero.vec.y;
	if (angle == 90)
	{
		pt_a->x = hero.vec.x - modulo(hero.vec.x, map.len_pix);
		if (pt_a->x == hero.vec.x)
			pt_a->x -= map.len_pix;
	}
	else if (angle == 270)
	{
		pt_a->x = hero.vec.x + (map.len_pix - modulo(hero.vec.x, map.len_pix));
		if (pt_a->x == hero.vec.x)
			pt_a->x += map.len_pix;
	}
}

void		get_vector_vert(double angle, int len_pix, t_vector *vector)
{
	if (angle > 180)
	{
		vector->x = len_pix;
		if (angle > 270)
			vector->y = -tan(convert(angle - 270)) * len_pix;
		else
			vector->y = tan(convert(270 - angle)) * len_pix;
	}
	else
	{
		vector->x = -len_pix;
		if (angle < 90)
			vector->y = tan(convert(angle + 90)) * len_pix;
		else
			vector->y = tan(convert(angle - 90)) * len_pix;
	}
}

t_loc		is_wall_vert(t_vect pt, double angle, t_param param)
{
	int		pt_y;
	t_loc	loc;

	loc.ret = -1;
	pt_y = (int)pt.y;
	loc.x = get_x(pt, angle, param);
	if (angle < 90 || angle > 270)
	{
		if (!(pt.y - pt_y) && !((int)pt.y % param.map.len_pix))
			loc.y = pt.y / param.map.len_pix - 1;
		else
			loc.y = pt.y / param.map.len_pix;
	}
	else
		loc.y = pt.y / param.map.len_pix;
	if ((loc.x < param.map.max_width && loc.x >= 0) && (loc.y < param.map.height && loc.y >= 0))
	{
		if (param.map.map[loc.y][loc.x] == '1')
			loc.ret = 1;
		else if (param.map.map[loc.y][loc.x] == '2')
			loc.ret = 2;
	}
	else
		loc.ret = 1;
	if (loc.ret < 0)
		loc.ret = 0;
	return (loc);
}

t_vect		get_pt_v(t_param param, t_map map, double angle)
{
	t_vect		pt_a;
	t_vector	vector;
	t_loc		loc;

	if (angle == 270 || angle == 90)
		get_pt_a_vert_90(param.hero, &pt_a, map, angle);
	else
		get_pt_a_vert(param.hero, &pt_a, map, angle);
	get_vector_vert(angle, map.len_pix, &vector);
	loc = is_wall_vert(pt_a, angle, param);
	if (loc.ret == 2 && !is_print_dist(loc, param.hero.vec, pt_a, param))
		loc.ret = 0;
	while (!loc.ret)
	{
		pt_a.x += vector.x;
		pt_a.y += vector.y;
		loc = is_wall_vert(pt_a, angle, param);
		if (loc.ret == 2 && !is_print_dist(loc, param.hero.vec, pt_a, param))
			loc.ret = 0;
	}
	if (loc.ret == 2)
	{
		pt_a.loc = loc;
		pt_a.wall = 2;
	}
	else
		pt_a.wall = 1;
	return (pt_a);
}
