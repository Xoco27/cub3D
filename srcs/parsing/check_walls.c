/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:55:04 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/18 15:10:45 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_surrounded(char **map, int y, int x)
{
	const int	dy[4] = {-1, 1, 0, 0};
	const int	dx[4] = {0, 0, -1, 1};
	int			k;
	int			ny;
	int			nx;

	k = 0;
	while (k < 4)
	{
		ny = y + dy[k];
		nx = x + dx[k];
		if (!is_inside_map(map, ny, nx)
			|| map[ny][nx] == ' ' || map[ny][nx] == '\0')
			return (false);
		k++;
	}
	return (true);
}

static bool	find_map_bounds(char **file, int *start, int *end)
{
	*start = 0;
	while (file[*start] && !is_map_line(file[*start]))
		(*start)++;
	if (!file[*start])
		return (false);
	*end = *start;
	while (file[*end])
		(*end)++;
	(*end)--;
	return (true);
}

static bool	check_top_bottom_walls(char **file, int start, int end)
{
	return (is_full_wall_line(file[start]) && is_full_wall_line(file[end]));
}

static bool	check_inner_line(char **file, int y)
{
	int	x;

	if (!is_line_closed(file[y]))
		return (false);
	x = 0;
	while (file[y][x])
	{
		if (is_open_cell(file[y][x]) && !is_surrounded(file, y, x))
			return (false);
		x++;
	}
	return (true);
}

bool	validate_walls(char **file)
{
	int	start;
	int	end;
	int	y;

	if (!file || !find_map_bounds(file, &start, &end))
		return (false);
	if (!check_top_bottom_walls(file, start, end))
		return (false);
	y = start;
	while (y <= end)
	{
		if (!check_inner_line(file, y))
			return (false);
		y++;
	}
	return (true);
}
