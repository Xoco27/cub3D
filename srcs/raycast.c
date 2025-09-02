/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/02 17:37:29 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render(t_data *data)
{
	int	i;

	i = 0;
	init_img(data, &data->img, 0);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw_floor_and_sky(data);
	ray_cast(data, i);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	return (0);
}

static void	ray_vert(t_data *data, double cos_a, double sin_a, int j)
{
	double	y_vert;
	double	x_vert;
	double	delta_depth;
	double	dx;
	double	dy;

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
	data->depth_vert = (x_vert - data->player.pos_x) / cos_a;
	y_vert = data->player.pos_y + data->depth_vert * sin_a;
	delta_depth = dx / cos_a;
	dy = delta_depth * sin_a;
	j = 0;
	while (j < data->max_depth)
	{
		if ((int)y_vert < 0 || (int)y_vert >= data->map.height
			|| (int)x_vert < 0 || (int)x_vert >= data->map.width)
			break ;
		if (data->tab[(int)y_vert][(int)x_vert] == '1')
			break ;
		x_vert += dx;
		y_vert += dy;
		data->depth_vert += delta_depth;
		j++;
	}
	data->y_vert = y_vert;
}

static void	ray_hori(t_data *data, double cos_a, double sin_a, int j)
{
	double	y_hori;
	double	x_hori;
	double	delta_depth;
	double	dx;
	double	dy;

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
	data->depth_hori = (y_hori - data->player.pos_y) / sin_a;
	x_hori = data->player.pos_x + data->depth_hori * cos_a;
	delta_depth = dy / sin_a;
	dx = delta_depth * cos_a;
	j = 0;
	while (j < data->max_depth)
	{
		if ((int)y_hori < 0 || (int)y_hori >= data->map.height
			|| (int)x_hori < 0 || (int)x_hori >= data->map.width)
			break ;
		if (data->tab[(int)y_hori][(int)x_hori] == '1')
			break ;
		x_hori += dx;
		y_hori += dy;
		data->depth_hori += delta_depth;
		j++;
	}
	data->x_hori = x_hori;
}

void	display_walls(t_data *data, double proj_height, double wall_x, int i)
{
	int		tex_y;
	char	*pixel;

	tex_y = (int)data->tex_pos & (TILE - 1);
	if (tex_y >= TILE)
		tex_y = TILE - 1;
	if (tex_y < 0)
		tex_y = 0;
	data->tex_pos += (double)TILE / proj_height;
	pixel = data->wall.addr + (tex_y * data->wall.line_len
			+ ((int)(wall_x * TILE)) * (data->wall.bpp / 8));
	my_mlx_pixel_put(&data->img, data->scale * i,
		data->win_height / 2 - proj_height / 2 + data->index, *(int *)pixel);
}

void	ray_cast(t_data *data, int i)
{
	double	ray_angle;
	double	depth;
	double	proj_height;
	double	wall_x;

	ray_angle = data->player.angle - data->fov / 2 + 0.0001;
	while (i < data->num_rays)
	{
		ray_vert(data, cos(ray_angle), sin(ray_angle), i);
		ray_hori(data, cos(ray_angle), sin(ray_angle), i);
		if (data->depth_vert < data->depth_hori)
		{
			depth = data->depth_vert;
			wall_x = fmod(data->y_vert, 1.0);
		}
		else
		{
			depth = data->depth_hori;
			wall_x = fmod(data->x_hori, 1.0);
		}
		depth *= cos(data->player.angle - ray_angle);
		proj_height = data->screen_dist / (depth);
		data->tex_pos = 0;
		data->index = 0;
		while (data->index < proj_height)
		{
			display_walls(data, proj_height, wall_x, i);
			data->index++;
		}
		ray_angle += data->delta_angle;
		i++;
	}
}
