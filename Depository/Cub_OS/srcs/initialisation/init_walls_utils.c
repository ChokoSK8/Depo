/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:45:02 by abrun             #+#    #+#             */
/*   Updated: 2021/02/09 15:59:48 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

char		*get_final_data(t_img img, t_param param)
{
	int			pos;
	t_point		p;
	int			coef_x;
	int			coef_y;
	char		*data_f;

	coef_x = param.width / img.width + 1;
	coef_y = param.height / img.height + 1;
	data_f = malloc(param.height * param.width * 3);
	if (data_f == NULL)
		return (NULL);
	p.y = 0;
	while (p.y < param.height)
	{
		p.x = 0;
		while (p.x < param.width)
		{
			pos = ((p.x / coef_x) * 4) + (img.size_line * (p.y / coef_y));
			*data_f++ = img.data[pos];
			*data_f++ = img.data[pos + 1];
			*data_f++ = img.data[pos + 2];
			p.x++;
		}
		p.y++;
	}
	return (data_f - (param.width * param.height));
}
