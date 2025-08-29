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

void	init_img(t_data *data, t_img *img, int flag)
{
	if (flag == 0)
	{
		img->img = mlx_new_image(data->mlx_ptr,
				data->win_width, data->win_height);
		img->addr = mlx_get_data_addr(img->img,
				&img->bpp, &img->line_len, &img->endian);
	}
	else if (flag == 1)
	{
		data->wall.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"assets/wall.xpm", &data->player.width, &data->player.height);
		data->wall.addr = mlx_get_data_addr(img->img,
				&img->bpp, &img->line_len, &img->endian);
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < TILE && y >= 0 && y < TILE)
	{
		char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int*)pixel = color;
	}

}
