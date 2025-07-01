/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/07/01 16:10:19 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray(t_data *data)
{
	while ()
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.pos_x + data->player.vector_x,
			data->player.pos_y + data->player.vector_y, 0x000000);
		data->player.vector_y += 1;
		printf("%f\n", data->player.vector_y);
	}
}
