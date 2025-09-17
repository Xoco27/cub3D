/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:38:56 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/17 18:19:54 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_line_closed(char *line)
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

static bool	is_full_wall_line(char *line)
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

bool	validate_walls(char **file, int i)
{
	int	start;
	int	end;

	if (!file)
		return (false);
	start = 0;
	while (file[start] && !is_map_line(file[start]))
		start++;
	if (!file[start])
		return (false);
	end = start;
	while (file[end])
		end++;
	end--;
	if (!is_full_wall_line(file[start]))
		return (false);
	i = start;
	while (i++ < end)
	{
		if (!is_line_closed(file[i]))
			return (false);
	}
	if (!is_full_wall_line(file[end]))
		return (false);
	return (true);
}
