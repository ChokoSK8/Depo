/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:43:55 by abrun             #+#    #+#             */
/*   Updated: 2021/03/19 09:42:16 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game.h"

void			get_param_x(t_param *param, t_vect pt_a)
{
	if (pt_a.dir == 1)
		param->x = ((int)round(pt_a.x) % param->map.len_pix) % param->wall.img.width;		
	else
		param->x = ((int)round(pt_a.y) % param->map.len_pix) % param->wall.img.width;
}

t_line			get_line_2_pts(t_vect pt_1, t_vector pt_2)
{
	t_line	d;

	if (round(pt_1.x) == round(pt_2.x))
		d.c = pt_1.x;
	else
	{
		d.c = 0;
		d.a = (pt_1.y - pt_2.y) / (pt_1.x - pt_2.x);
	}
	d.b = pt_1.y - pt_1.x * d.a;
	return (d);
}

double			get_dist(t_vector pt_1, t_vect pt_2)
{
	double		dist;

	dist = sqrt(pow(pt_1.x - pt_2.x, 2) + pow(pt_1.y - pt_2.y, 2));
	return (dist);
}

t_vector		get_end_spe(t_vect cube, double angle, t_vector *end_2)
{
	t_vector	end;

	if (angle == 0 || angle == 180)
	{
		end.y = cube.y;
		end_2->y = cube.y;
		if (angle == 0)
		{
			end_2->x = cube.x + 32;
			end.x = cube.x - 32;
		}
		else
		{
			end_2->x = cube.x - 32;
			end.x = cube.x + 32;
		}
	}
	else
	{
		end.x = cube.x;
		end_2->x = cube.x;
		if (angle == 90)
		{
			end.y = cube.y - 32;
			end_2->y = cube.y + 32;
		}
		else
		{
			end.y = cube.y + 32;
			end_2->y = cube.y - 32;
		}
	}
	return (end);
}

void			change_end_2(t_vector *end_2, t_vector end_1)
{
	end_2->x = end_1.x;
	end_2->y = end_1.y;
}

t_vector		get_end(t_line d, t_vect cen, double angle, t_vector *end_2)
{
	t_eq		eq;
	t_vector	end_1;
	t_vector	end;

	if (angle != 0.0000 && angle != 90.0000 && angle != 180.0000 && angle != 270.0000)
	{
		eq.a = 1 + pow(d.a, 2);
		eq.b = -2 * cen.x - 2 * d.a * cen.y + 2 * d.a * d.b;
		eq.c = -1024 + pow(cen.x, 2) - 2 * cen.y * d.b + pow(cen.y, 2) + pow(d.b, 2);
		eq.d = pow(eq.b, 2) - 4 * eq.a * eq.c;
		end_1.x = (-eq.b - sqrt(eq.d)) / (2 * eq.a);
		end_2->x = (-eq.b + sqrt(eq.d)) / (2 * eq.a);
		end_1.y = d.a * end_1.x + d.b;
		end_2->y = d.a * end_2->x + d.b;
		if (angle <= 90)
		{
			if (round(end_1.x) < round(end_2->x))
				end = end_1;
			else if (round(end_1.x) != round(end_2->x))
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
			else if (round(end_1.y) < round(end_2->y))
				end = end_1;
			else
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
		}
		else if (angle > 90 && angle <= 180)
		{
			if (round(end_1.x) > round(end_2->x))
				end = end_1;
			else if (round(end_1.x) != round(end_2->x))
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
			else if (round(end_1.y) < round(end_2->y))
				end = end_1;
			else
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
		}
		else if (angle > 180 && angle <= 270)
		{
			if (end_1.x > end_2->x)
				end = end_1;
			else if (end_1.x != end_2->x)
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
			else if (end_1.y > end_2->y)
				end = end_1;
			else
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
		}
		else
		{
			if (end_1.x < end_2->x)
				end = end_1;
			else if (end_1.x != end_2->x)
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
			else if (end_1.y > end_2->y)
				end = end_1;
			else
			{
				end = *end_2;
				change_end_2(end_2, end_1);
			}
		}
	}
	else
		end = get_end_spe(cen, angle, end_2);
	return (end);
}

t_line			get_d_perpendicular(t_line d, t_vect pt)
{
	t_line		d_2;

	if (d.c)
		d_2.a = 0;
	else
		d_2.a = -1.0000 / d.a;
	if (d.a == 0)
		d_2.c = pt.x;
	else
		d_2.c = 0;
	d_2.b = pt.y - d_2.a * pt.x;
	return (d_2);
}

int				get_x_sprite(t_vector pt_1, t_vect pt_2)
{
	double		dist;
	int			x;

	dist = get_dist(pt_1, pt_2) / 2;
	x = round(dist);
	return (x);
}

t_vect		get_inter(t_line d_1, t_line d_2)
{
	t_vect		inter;

	if (d_1.c)
		inter.x = d_1.c;
	else if (d_2.c)
		inter.x = d_2.c;
	else
		inter.x = (d_2.b - d_1.b) / (d_1.a - d_2.a);
	if (d_1.c)
		inter.y = d_2.a * inter.x + d_2.b;
	else
		inter.y = d_1.a * inter.x + d_1.b;
	return (inter);
}

int				is_print(t_vect pt, t_vector end_1, t_vector end_2)
{
	double	d_1;
	double	d_2;

	d_1 = get_dist(end_1, pt);
	d_2 = get_dist(end_2, pt);
	if (d_1 >= 62.000 || d_2 >= 62.000)
		return (0);
	return (1);
}

double			conv_rad(double rad)
{
	double	deg;

	deg = rad * 57.2958;
	return (deg);
}

double			get_angle_sprite(t_vector hero, t_vect cube)
{
	double		angle;

	if (hero.y >= cube.y && hero.x <= cube.x)
		angle = 90 - conv_rad(acos((cube.x - hero.x) / get_dist(hero, cube)));
	else if (hero.y <= cube.y && hero.x <= cube.x)
		angle = 180 - conv_rad(acos((cube.y - hero.y) / get_dist(hero, cube)));
	else if (hero.y >= cube.y && hero.x >= cube.x)
		angle = 360 - conv_rad(acos((hero.y - cube.y) / get_dist(hero, cube)));
	else
		angle = 270 - conv_rad(acos((hero.x - cube.x) / get_dist(hero, cube)));
	return (angle);
}

t_line			get_d_angle_hero(t_player hero, t_map map)
{
	t_line		d;
	t_vect		pt;

	if ((hero.angle > 315 || hero.angle < 45)
			|| (hero.angle > 135 && hero.angle < 225))
		get_pt_a_hori(hero, &pt, map, hero.angle);
	else
		get_pt_a_vert(hero, &pt, map, hero.angle);
	d = get_line_2_pts(pt, hero.vec);
	return (d);
}

double			display_sprite(int *n_wall, t_param *param, double counter, t_vect pt)
{
	t_vector	end;
	t_vector	end_2;
	t_line		d;
	t_line		d_2;
	t_vect		cube;
	double		angle;
	double		n;
	t_loc		sp;
	double		dist;

	sp.x = pt.loc.x;
	sp.y = pt.loc.y;
	n = 30 / (double)param->width;
	cube.x = (pt.loc.x + 0.5) * param->map.len_pix;
	cube.y = (pt.loc.y + 0.5) * param->map.len_pix;
	d = get_line_2_pts(cube, param->hero.vec);
	d_2 = get_d_perpendicular(d, cube);
	angle = get_angle_sprite(param->hero.vec, cube);
	end = get_end(d_2, cube, angle, &end_2);
	while (counter > -15 && pt.wall == 2 && pt.loc.x == sp.x && pt.loc.y == sp.y)
	{
		angle = get_angle_right(param->hero.angle, counter);
		d = get_line_2_pts(pt, param->hero.vec);
		pt = get_inter(d, d_2);
		dist = get_d(param->hero, pt, counter);
		param->wall = param->walls.sprite;
		get_wall_dim(&param->wall, dist, param, angle);
		param->x = get_x_sprite(end, pt);
		if (is_print(pt, end, end_2))
			draw_wall(param->wall, *n_wall, param, 0xFF);
		*n_wall += 1;
		counter -= n;
		if (angle != 0 && angle != 90 && angle != 180 && angle != 270)
			pt = get_dist_min(get_pt_h(*param, param->map, angle),
					get_pt_v(*param, param->map, angle), param, angle);
		else
			pt = get_pt_a_90(param, angle);
	}
	return (counter);
}

void			display_multi_angle(t_param *param, int color)
{
	double			counter;
	t_vect			pt_a;
	double			n;
	int				n_wall;
	double			angle;

	n = 30 / (double)param->width;
	angle = 0;
	n_wall = 0;
	counter = 15;
	while (counter > -15)
	{
		angle = get_angle_right(param->hero.angle, counter);
		if (angle != 0 && angle != 90 && angle != 180 && angle != 270)
			pt_a = get_dist_min(get_pt_h(*param, param->map, angle),
					get_pt_v(*param, param->map, angle), param, angle);
		else
			pt_a = get_pt_a_90(param, angle);
		if (pt_a.wall == 2)
			counter = display_sprite(&n_wall, param, counter, pt_a);
		else
		{
			get_param_x(param, pt_a);
			get_wall_dim(&param->wall, get_d(param->hero, pt_a, counter), param, angle);
			draw_wall(param->wall, n_wall, param, color);
			n_wall++;
			counter -= n;
		}
	}
}

void			draw_wall(t_wall wall, int pos_x, t_param *param, int color)
{
	int			y;
	int			pos;
	int			start_y;

	y = 0;
	start_y = (param->height - wall.height) / 2;
	if (color)
	{
		dis_textures(wall, param, pos_x);
	}
	else
	{
		while (y < wall.height)
		{
			pos = (pos_x * 4) + (param->img.size_line * (start_y + y));
			if (start_y + y >= 0 && start_y + y < param->height)
			{
				param->img.data[pos] = color;
				param->img.data[pos + 1] = color;
				param->img.data[pos + 2] = color;
			}
			y++;
		}
	}
}

void			dis_textures(t_wall wall, t_param *param, int pos_x)
{
	int			y;
	int			start_y;
	int			pos;
	int			pos_2;
	double		y_2;

	y_2 = 0;
	y = 0;
	start_y = (param->height - wall.height) / 2;
	while (y < wall.height)
	{
		if (start_y + y >= 0 && start_y + y < param->height)
		{
			pos = (pos_x % param->width * 4) + (param->img.size_line * (start_y + y));
			pos_2 = (param->x * 4) +
				(wall.img.size_line * ((int)y_2 % wall.img.height));
			param->img.data[pos] = param->wall.img.data[pos_2];
			param->img.data[pos + 1] = param->wall.img.data[pos_2 + 1];
			param->img.data[pos + 2] = param->wall.img.data[pos_2 + 2];
		}
		y_2 += wall.coef;
		y++;
	}
}
