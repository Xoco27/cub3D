/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:26:38 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/17 18:08:31 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	depth_wall_x(t_data *data, double *depth, double *wall_x, int flag)
{
	if (flag == 0)
	{
		*depth = data->depth_vert;
		*wall_x = fmod(data->y_vert, 1.0);
		if (data->cos_a > 0)
			data->tex = data->img[3];
		else
			data->tex = data->img[4];
	}
	else
	{
		*depth = data->depth_hori;
		*wall_x = fmod(data->x_hori, 1.0);
		if (data->sin_a > 0)
			data->tex = data->img[2];
		else
			data->tex = data->img[1];
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
		if (data->tab[(int)y_vert][(int)x_vert] == '1'
			|| data->tab[(int)y_vert][(int)x_vert] == ' ')
			break ;
		x_vert += dx;
		y_vert += dy;
		data->depth_vert += delta_depth;
		j++;
	}
	return (y_vert);
}

static int	check_map_collision(t_data *data, double x_hori, double y_hori)
{
	int	iy;

	iy = (int)y_hori;
	if (iy < 0 || iy >= data->map.height)
		return (1);
	if ((int)x_hori < 0 || (int)x_hori >= (int)ft_strlen(data->tab[iy]))
		return (1);
	if (data->tab[iy][(int)x_hori] == '1' || data->tab[iy][(int)x_hori] == ' ')
		return (1);
	return (0);
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
		if (check_map_collision(data, x_hori, y_hori))
			break ;
		x_hori += dx;
		y_hori += dy;
		data->depth_hori += delta_depth;
		j++;
	}
	return (x_hori);
}

void	wh(t_data *data)
{
	int	i;
	int	j;

	data->map.width = 0;
	j = 0;
	while (data->tab[j])
	{
		i = 0;
		while (data->tab[j][i])
			i++;
		if (i > data->map.width)
			data->map.width = i;
		j++;
	}
	data->map.height = j;
	data->player.width = TILE;
	data->player.height = TILE;
	pos(data->tab, data);
}
