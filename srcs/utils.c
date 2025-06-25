/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:17:51 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:09:04 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	check_es(char **map)
{
	int	x;
	int	y;
	int	e;
	int	s;

	y = 0;
	e = 0;
	s = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
				e++;
			if (map[y][x] == 'P')
				s++;
			x++;
		}
		y++;
	}
	if (e != 1 || s != 1)
		return (0);
	return (1);
}

void	error(char **map)
{
	free(map);
	perror("Error\nCan't open file.");
}

void	score(t_data *data)
{
	if (data->map[data->player.pos_y][data->player.pos_x] == 'C')
	{
		data->score--;
		data->map[data->player.pos_y][data->player.pos_x] = '0';
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
