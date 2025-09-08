/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/08 20:00:45 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render(t_data *data)
{
	int	i;

	i = 0;
	draw_floor_and_sky(data);
	ray_cast(data, i);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img[0].img, 0, 0);
	return (0);
}

static void	ray_vert(t_data *data, double cos_a, double sin_a)
{
	double	x_vert;
	double	dx;

	data->cos_a = cos_a;
	data->sin_a = sin_a;
	if (cos_a > 0)
	{
		x_vert = data->map.map_x + 1;
		dx = 1;
	}
	else
	{
		x_vert = data->map.map_x - 0.000001;
		dx = -1;
	}
	data->y_vert = ray_vert_loop(data, x_vert, dx);
}

static void	ray_hori(t_data *data, double cos_a, double sin_a)
{
	double	y_hori;
	double	dy;

	data->cos_a = cos_a;
	data->sin_a = sin_a;
	if (sin_a > 0)
	{
		y_hori = data->map.map_y + 1;
		dy = 1;
	}
	else
	{
		y_hori = data->map.map_y - 0.000001;
		dy = -1;
	}
	data->x_hori = ray_hori_loop(data, y_hori, dy);
}

static void	display_walls(t_data *data,
	double proj_height, double wall_x, int i)
{
	int		tex_x;
	int		tex_y;
	char	*pixel;

	tex_x = (int)(wall_x * TILE);
	tex_y = (int)data->tex_pos;
	data->tex_pos += (double)TILE / proj_height;
	pixel = data->tex.addr + (tex_y * data->tex.line_len
			+ tex_x * (data->tex.bpp / 8));
	my_mlx_pixel_put(&data->img[0], data->scale * i,
		data->win_height / 2 - proj_height / 2 + data->index,
		*(int *)pixel);
}

void	ray_cast(t_data *data, int i)
{
	double	ray_angle;
	double	depth;
	double	proj_height;
	double	wall_x;

	ray_angle = data->player.angle - data->fov / 2 + 0.0001;
	while (i++ < data->num_rays)
	{
		ray_vert(data, cos(ray_angle), sin(ray_angle));
		ray_hori(data, cos(ray_angle), sin(ray_angle));
		if (data->depth_vert < data->depth_hori)
			depth_wall_x(data, &depth, &wall_x, 0);
		else
			depth_wall_x(data, &depth, &wall_x, 1);
		depth *= cos(data->player.angle - ray_angle);
		proj_height = data->screen_dist / (depth);
		data->tex_pos = 0;
		data->index = 0;
		while (proj_height > 0 && data->index < proj_height)
		{
			display_walls(data, proj_height, wall_x, i);
			data->index++;
		}
		ray_angle += data->delta_angle;
	}
}
