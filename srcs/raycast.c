/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:58 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/26 18:29:12 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static void	ray_vert(t_data *data)
// {
	
// }

// static void	ray_hori(t_data *data)
// {
	
// }

void	ray_cast(t_data *data)
{
	double	ray_angle;
	double	sin_a;
	double	cos_a;
	double	x_vert;
	double	y_vert;
	double	x_hori;
	double	y_hori;
	double	dx;
	double	dy;
	double	depth_vert;
	double	depth_hori;
	double	delta_depth;
	double	depth;
	int		i;
	int		j;

	i = 0;
	ray_angle = data->player.angle - data->fov / 2 + 0.0001;
	while (i < data->num_rays)
	{
		j = 0;
		cos_a = cos(ray_angle);
		sin_a = sin(ray_angle);

		//hori
		if (sin_a > 0)
		{
			y_hori = data->img.map_y + 1;
			dy = 1;
		}
		else
		{
			y_hori = data->img.map_y - 0.000001;
			dy = -1;
		}
		depth_hori = (y_hori - data->player.pos_y) / sin_a;
		x_hori = data->player.pos_x + depth_hori * cos_a;
		delta_depth = dy / sin_a;
		dy = delta_depth * cos_a;

		while (j < data->max_depth)
		{
			if ((int)y_hori <= 0 && (int)y_hori > data->img.height
				&& (int)x_hori <= 0 && (int)x_hori > data->img.width
				&& data->map[(int)y_hori][(int)x_hori] == '1')
				break ;
			x_hori += dx;
			y_hori += dy;
			depth_vert += delta_depth;
			j++;
		}
		//vert
		if (cos_a > 0)
		{
			x_vert = data->img.map_x + 1;
			dx = 1;
		}
		else
		{
			x_vert = data->img.map_x - 0.000001;
			dx = -1;
		}
		depth_vert = (x_vert - data->player.pos_x) / cos_a;
		y_vert = data->player.pos_y + depth_vert * sin_a;
		delta_depth = dx / cos_a;
		dy = delta_depth * sin_a;

		while (j < data->max_depth)
		{
			if ((int)y_vert <= 0 && (int)y_vert > data->img.height
				&& (int)x_vert <= 0 && (int)x_vert > data->img.width
				&& data->map[(int)y_vert][(int)x_vert] == '1')
				break ;
			x_vert += dx;
			y_vert += dy;
			depth_vert += delta_depth;
			j++;
		}
		if (depth_vert < depth_hori)
			depth = depth_vert;
		else
			depth = depth_hori;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.pos_x * TILE * depth * cos_a,
			data->player.pos_y * TILE * depth * sin_a,
			0xffffff);
		ray_angle += data->delta_angle;
		i++;
	}
}

// void	rotate(t_data *data)
// {
	
// }
