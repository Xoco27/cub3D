/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:19:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:09:01 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_exit(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->score == 0)
	{
		while (data->map[y])
		{
			x = 0;
			while (data->map[y][x])
			{
				if (data->map[y][x] == 'E')
					print_img(data->img.exit_opened, x, y, data);
				x++;
			}
			y++;
		}
	}
}

void	make_copy(char **map, char ***copy, int y)
{
	int	i;

	i = 0;
	*copy = malloc((y + 1) * sizeof(char *));
	if (!*copy)
		return ;
	while (map[i])
	{
		(*copy)[i] = ft_strdup(map[i]);
		if (!(*copy)[i])
		{
			free_map((*copy));
			return ;
		}
		i++;
	}
	(*copy)[i] = NULL;
}

int	check_paths(t_data *data, int x, int y)
{
	if (data->copy[y][x] == '1' || data->copy[y][x] == 'V')
		return (0);
	if (data->copy[y][x] == 'C')
		data->total--;
	if (data->copy[y][x] == 'P')
		data->r = 1;
	data->copy[y][x] = 'V';
	check_paths(data, x + 1, y);
	check_paths(data, x - 1, y);
	check_paths(data, x, y + 1);
	check_paths(data, x, y - 1);
	if (data->r == 1 && data->total == 0)
		return (1);
	return (0);
}

int	is_map_valid(t_data *data)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'E')
			{
				end_x = x;
				end_y = y;
			}
			x++;
		}
		y++;
	}
	x = check_paths(data, end_x, end_y);
	free_map(data->copy);
	if (x == 1)
		return (1);
	return (0);
}

int	another_check(t_data *data)
{
	int	y;

	y = 0;
	while (data->map[y])
		y++;
	data->score = check(data->map);
	data->total = data->score;
	data->r = 0;
	if (non_valid(data->map) == 1)
	{
		free_map(data->map);
		return (1);
	}
	if (data->score == 0)
	{
		free_map(data->map);
		return (1);
	}
	make_copy(data->map, &data->copy, y);
	if (is_map_valid(data) == 0)
	{
		free_map(data->map);
		return (perror("Error\n Map cannot be finished"), 1);
	}
	return (0);
}
