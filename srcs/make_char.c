/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:00:15 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 12:10:36 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
			if (map[y][x] == 'P')
			{
				data->player.pos_x = x;
				data->player.pos_y = y;
				return ;
			}
			x++;
		}
		y++;
		data->player.angle = 0;
		data->fov = PI / 3;
		data->num_rays = data->win_width / 2;
		data->delta_angle = data->fov / data->num_rays;
		data->max_depth = 20;
		data->screen_dist = (data->win_width / 2) / tan(data->fov / 2);
		data->scale = data->win_width / data->num_rays;
	}
}
