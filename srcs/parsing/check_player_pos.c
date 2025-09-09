/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:48:40 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/09 17:13:56 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_player(char **file, int i, int j,
		int start, int *player_count)
{
	(*player_count)++;
	if (i == start || !file[i + 1] || j == 0 || !file[i][j + 1]
		|| file[i - 1][j] == ' ' || file[i + 1][j] == ' '
		|| file[i][j - 1] == ' ' || file[i][j + 1] == ' ')
		return (0);
	return (1);
}

int	validate_player_position(char **file, int i)
{
	int	j;
	int	player_count;
	int	start;

	player_count = 0;
	start = 0;
	while (file[start] && !is_map_line(file[start]))
		start++;
	if (!file[start])
		return (0);
	i = start;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == 'N' || file[i][j] == 'S'
				|| file[i][j] == 'E' || file[i][j] == 'W')
				if (!check_player(file, i, j, start, &player_count))
					return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
