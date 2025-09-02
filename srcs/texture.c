/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:43:18 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/02 13:21:12 by cfleuret         ###   ########.fr       */
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
		img->height = data->win_height;
		img->width = data->win_width;
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

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

static int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_floor_and_sky(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < data->win_width)
	{
		j = 0;
		while (j < data->win_height)
		{
			if (j < data->win_height / 2)
				my_mlx_pixel_put(&data->img, i, j, trgb(0, 0, 150, 255));
			else
				my_mlx_pixel_put(&data->img, i, j, trgb(0, 80, 80, 80));
			j++;
		}
	}
	++i;
}
