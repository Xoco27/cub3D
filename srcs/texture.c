/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:43:18 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 14:11:46 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			data->win_width, data->win_height);
	data->img.addr = mlx_get_data_addr(&data->img.mlx_img,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
}


