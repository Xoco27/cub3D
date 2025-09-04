/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:38:56 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/08/28 13:23:06 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_line_closed(char *line)
{
	int i = 0;

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

static bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == 'F' || *line == 'C')
			return (false);
		else if (*line == '1')
			return (true);
		line++;
	}
	return (false);
}

bool	validate_walls(char **file)
{
	int	start = 0;
	int	i = 0;

	if (!file)
		return (false);
	while (file[start] && !is_map_line(file[start]))
		start++;
	if (!file[start])
		return (false);
	if (!is_line_closed(file[start]))
		return (false);
	i = start + 1;
	while (file[i + 1])
	{
		if (file[i + 1] && file[i + 2] == NULL)
			break ;
		if (!is_line_closed(file[i]))
			return (false);
		i++;
	}
	if (!is_line_closed(file[i]))
		return (false);

	return (true);
}
