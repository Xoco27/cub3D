/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/07/04 10:34:36 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray(t_data *data)
{
	// int	x;
	// int	y;

	// x = 0;
	// y = 0;
	data->img.map_x += data->player.vector_x;
	data->img.map_y += data->player.vector_y;
	while (data->img.map_y >= 0 && data->img.map_y < data->img.height
		&& data->img.map_x >= 0 && data->img.map_x < data->img.width
		&& data->map[data->img.map_y][data->img.map_x] != '1')
	{
		// while (x < TILE * data->player.pos_x && y < TILE * data->player.pos_y)
		// {
		// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr,
		// 		data->player.pos_x * TILE + x,
		// 		data->player.pos_y * TILE + y,
		// 		0xffffff);
		// 	x += data->player.vector_x;
		// 	y += data->player.vector_y;
		// }
		data->img.map_x += data->player.vector_x;
		data->img.map_y += data->player.vector_y;
	}
	printf("%d %d\n", data->img.map_x, data->img.map_y);
}

// void	rotate(t_data *data)
// {
	
// }
