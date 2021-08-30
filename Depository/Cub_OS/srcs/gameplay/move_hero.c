/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:00:55 by abrun             #+#    #+#             */
/*   Updated: 2021/03/23 11:10:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

int			move_hero(int key, t_param *param)
{
	display_background(*param);
	if (key == 53)
	{
		mlx_destroy_window(param->mlx, param->win);
		free_param(param);
		printf("\nTest des leaks\n");
		system("leaks a.out | grep leaked\n");
		exit(0);
	}
	if (key == 12)
		move_key_12(&param->hero, param->img_map);
	if (key == 6)
		move_key_6(&param->hero, param->img_map);
	if (key == 2)
		param->hero.angle -= 1;
	if (key == 1)
		param->hero.angle += 1;
	if (param->hero.angle < 0)
		param->hero.angle += 360;
	if (param->hero.angle > 360)
		param->hero.angle %= 360;
	display_multi_angle(param, 0xFF);
	mlx_put_image_to_window(param->mlx, param->win, param->img.image, 0, 0);
	return (1);
}

void		move_key_12(t_player *hero, t_img img)
{
	if (!is_wall_12(*hero, img))
	{
		hero->vec.y -= hero->speed *
				cos(convert(hero->angle));
		hero->vec.x -= hero->speed *
				sin(convert(hero->angle));
	}
}

void		move_key_6(t_player *hero, t_img img)
{
	if (!is_wall_6(*hero, img))
	{
		hero->vec.y += hero->speed *
				cos(convert(hero->angle));
		hero->vec.x += hero->speed *
				sin(convert(hero->angle));
	}
}
