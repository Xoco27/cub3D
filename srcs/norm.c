/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:26:38 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/02 18:02:41 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	depth_wall_x(t_data *data, double *depth, double *wall_x, int flag)
{
	if (flag == 0)
	{
		*depth = data->depth_vert;
		*wall_x = fmod(data->y_vert, 1.0);
	}
	else
	{
		*depth = data->depth_hori;
		*wall_x = fmod(data->x_hori, 1.0);
	}
}

double	ray_vert_loop(t_data *data, double x_vert, double dx)
{
	double	dy;
	double	delta_depth;
	int		j;
	double	y_vert;

	data->depth_vert = (x_vert - data->player.pos_x) / data->cos_a;
	y_vert = data->player.pos_y + data->depth_vert * data->sin_a;
	delta_depth = dx / data->cos_a;
	dy = delta_depth * data->sin_a;
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
	return (y_vert);
}

double	ray_hori_loop(t_data *data, double y_hori, double dy)
{
	double	x_hori;
	double	delta_depth;
	double	dx;
	int		j;

	data->depth_hori = (y_hori - data->player.pos_y) / data->sin_a;
	x_hori = data->player.pos_x + data->depth_hori * data->cos_a;
	delta_depth = dy / data->sin_a;
	dx = delta_depth * data->cos_a;
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
	return (x_hori);
}
