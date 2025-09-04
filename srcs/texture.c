/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:43:18 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/04 13:09:13 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_data *data, t_img *img)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i == 0)
		{
			img[i].img = mlx_new_image(data->mlx_ptr,
					data->win_width, data->win_height);
			img[i].height = data->win_height;
			img[i].width = data->win_width;
		}
		else
		{
			img[i].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->assets[i - 1], &data->player.width,
					&data->player.height);
		}
		img[i].addr = mlx_get_data_addr(img[i].img,
				&img[i].bpp, &img[i].line_len, &img[i].endian);
		i++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
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
				my_mlx_pixel_put(&data->img[0], i, j, trgb(0, 0, 150, 255));
			else
				my_mlx_pixel_put(&data->img[0], i, j, trgb(0, 80, 80, 80));
			j++;
		}
	}
	++i;
}
