/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:48:40 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/04 14:52:17 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	validate_player_position(char **file)
{
	int		i;
	int		j;
	int		player_count;
	int		start;

	player_count = 0;
	start = 0;
	while (file[start] && !is_map_line(file[start]))
		start++;
	if (!file[start])
		return (0);
	for (i = start; file[i]; i++)
	{
		for (j = 0; file[i][j]; j++)
		{
			if (file[i][j] == 'N' || file[i][j] == 'S'
				|| file[i][j] == 'E' || file[i][j] == 'W')
			{
				player_count++;

				if (i == start || !file[i + 1] || j == 0
					|| !file[i][j + 1]
					|| file[i - 1][j] == ' '
					|| file[i + 1][j] == ' '
					|| file[i][j - 1] == ' '
					|| file[i][j + 1] == ' ')
					return (0);
			}
		}
	}
	return (player_count == 1);
}
