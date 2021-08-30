/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:23:18 by abrun             #+#    #+#             */
/*   Updated: 2021/01/28 11:20:51 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

void		free_param(t_param *param)
{
	int		counter;

	counter = 0;
	free(param->no);
	free(param->sp);
	free(param->so);
	free(param->ea);
	free(param->we);
	free(param->floor);
	free(param->roof);
	free(param->img.data);
	free(param->walls.wall1.img.data);
	free(param->walls.wall2.img.data);
	free(param->walls.wall3.img.data);
	free(param->walls.wall4.img.data);
	free(param->walls.sprite.img.data);
	while (param->map.map[counter])
		free(param->map.map[counter++]);
	free(param->map.map);
	free(param->img_map.data);
}

void		free_tab_checks(t_param *param)
{
	if (param->checks[0] == 1)
		free(param->no);
	if (param->checks[1] == 1)
		free(param->so);
	if (param->checks[2] == 1)
		free(param->ea);
	if (param->checks[3] == 1)
		free(param->we);
	if (param->checks[5] == 1)
		free(param->roof);
	if (param->checks[6] == 1)
		free(param->floor);
	if (param->checks[7] == 1)
		free(param->sp);
	free(param->tab);
}

void		free_map_param(t_param *param)
{
	int		counter;

	counter = 0;
	free(param->no);
	free(param->sp);
	free(param->so);
	free(param->ea);
	free(param->we);
	free(param->floor);
	free(param->roof);
	free(param->walls.wall1.img.data);
	free(param->walls.wall2.img.data);
	free(param->walls.wall3.img.data);
	free(param->walls.wall4.img.data);
	free(param->walls.sprite.img.data);
	while (param->map.map[counter])
		free(param->map.map[counter++]);
	free(param->map.map);
}

void		free_in_loop(t_param *param, int i, char **map)
{
	free_tab_checks(param);
	while (i--)
		free(map[i]);
	free(map);
}
