/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:00:15 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/09 18:21:32 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void	init_data(t_data *data)
{
	data->player.angle = 0;
	data->fov = PI / 3;
	data->num_rays = data->win_width / 2;
	data->delta_angle = data->fov / data->num_rays;
	data->max_depth = data->win_width;
	data->screen_dist = (data->win_width) / 2 / tan(data->fov / 2);
	data->scale = data->win_width / data->num_rays;
}

static	void	init_char(t_data *data, double angle, int x, int y)
{
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	data->map.map_x = x;
	data->map.map_y = y;
	data->player.angle = angle;
}

static void	check_pos(t_data *data, int x, int y, char **map)
{
	if (map[y][x] == 'N')
	{
		init_char(data, 270 * PI / 180, x, y);
		return ;
	}
	if (map[y][x] == 'W')
	{
		init_char(data, 180 * PI / 180, x, y);
		return ;
	}
	if (map[y][x] == 'S')
	{
		init_char(data, 90 * PI / 180, x, y);
		return ;
	}
	if (map[y][x] == 'E')
	{
		init_char(data, 0, x, y);
		return ;
	}
}

void	pos(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			check_pos(data, x, y, map);
			x++;
		}
		y++;
		init_data(data);
	}
}
