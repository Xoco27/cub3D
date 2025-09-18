/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:38:56 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/18 14:59:43 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_line_closed(char *line)
{
	int	i;

	i = 0;
	while (line[i] && isspace((unsigned char)line[i]))
		i++;
	if (line[i] != '1')
		return (false);
	while (line[i])
		i++;
	while (i > 0 && isspace((unsigned char)line[i - 1]))
		i--;
	if (line[i - 1] != '1')
		return (false);
	return (true);
}

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == 'F' || *line == 'C' || ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0)
			return (false);
		else if (*line == '1')
			return (true);
		line++;
	}
	return (false);
}

bool	is_full_wall_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace((unsigned char)line[i]) && line[i] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	is_inside_map(char **map, int y, int x)
{
	return (y >= 0 && map[y] && x >= 0 && x < (int)ft_strlen(map[y]));
}

bool	is_open_cell(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
