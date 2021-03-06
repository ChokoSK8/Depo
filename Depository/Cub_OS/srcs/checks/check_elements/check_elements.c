/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:13:27 by abrun             #+#    #+#             */
/*   Updated: 2021/03/24 12:16:52 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game.h"

int		check_syntaxe(char *s, size_t len, char *line, char *id)
{
	if (!ft_strnstr(line, s, len))
	{
		ft_printf("Erreur de syntaxe pour l'élément : %s\n", id);
		return (0);
	}
	return (1);
}

int		check_texture(char *id, char *line)
{
	int		fd;
	size_t	id_len;

	id_len = ft_strlen(id);
	while (ft_isspace(*line))
		line++;
	if (!check_syntaxe(id, id_len, line, id))
		return (0);
	line += id_len;
	while (ft_isspace(*line))
		line++;
	if (!check_syntaxe("./", 2, line, id))
		return (0);
	line += 2;
	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Erreur sur le chemin de la texture : %s\n", id);
		return (0);
	}
	return (1);
}

int		check_rgb(char *line, int id)
{
	int		counter;
	int		loop;

	loop = 3;
	while (loop--)
	{
		counter = 3;
		while (*line && *line != ',' && ft_isdigit(*line))
		{
			line++;
			counter--;
		}
		if (counter < 0 || counter == 3)
		{
			ft_printf("Erreur de syntaxe pour l'élément : %c\n", id);
			return (0);
		}
		*line && loop ? line++ : line;
	}
	if (*line)
	{
		ft_printf("Erreur de syntaxe pour l'élément : %c\n", id);
		return (0);
	}
	return (1);
}

int		check_color(int id, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_strnchr(line, id, 1))
	{
		ft_printf("Erreur de syntaxe pour l'élément : %c\n", id);
		return (0);
	}
	line++;
	while (ft_isspace(*line))
		line++;
	if (!check_rgb(line, id))
		return (0);
	return (1);
}

int		check_resolution(int id, char *line)
{
	if (!ft_strnchr(line, id, 1))
	{
		ft_printf("Erreur de syntaxe pour l'élément : %c\n", id);
		return (0);
	}
	line++;
	while (ft_isspace(*line))
		line++;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	while (ft_isdigit(*line))
		line++;
	if (*line)
	{
		ft_printf("Erreur de syntaxe pour l'élément : %c\n", id);
		return (0);
	}
	return (1);
}
