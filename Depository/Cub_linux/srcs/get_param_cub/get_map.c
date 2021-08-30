/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:59:57 by abrun             #+#    #+#             */
/*   Updated: 2021/01/28 11:03:17 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

int			fill_tab_map(char *line, int fd, char *tab, t_param *param)
{
	int		done;

	done = 1;
	tab += ft_strcpy(tab, line);
	*tab++ = '\n';
	free(line);
	while (done)
	{
		if ((done = get_next_line(fd, &line, 30)) == -1)
		{
			free_tab_checks(param);
			free(line);
			ft_putstr_fd("Erreur lors de la lecture du fichier !\n", 1);
			return (0);
		}
		tab += ft_strcpy(tab, line);
		free(line);
		*tab++ = '\n';
	}
	*(tab - 1) = 0;
	return (1);
}

char		**get_map(char *tab, t_param *param)
{
	char		**map;
	int			i;
	int			max_width;

	max_width = get_max_width(tab);
	if (!(map = malloc(sizeof(int *) * (get_height(tab) + 1))))
	{
		free_tab_checks(param);
		printf("Un malloc a échoué !\n");
		return (0);
	}
	if (!(i = loop_get_map(tab, map, max_width, param)))
		return (0);
	map[i] = 0;
	return (map);
}

int			loop_get_map(char *tab, char **map, int max_width, t_param *param)
{
	int		i;
	int		j;

	i = 0;
	while (*tab)
	{
		j = 0;
		map[i] = 0;
		if (!(map[i] = malloc(sizeof(int) * (max_width + 1))))
		{
			printf("Un malloc a échoué !\n");
			free_in_loop(param, i, map);
			return (0);
		}
		while (*tab && *tab != '\n')
			if (*tab == '\t')
				tab += fill_tabulation(map, i, &j);
			else
				map[i][j++] = *tab++;
		while (j < max_width)
			map[i][j++] = 32;
		map[i++][j] = 0;
		*tab ? tab++ : tab;
	}
	return (i);
}
