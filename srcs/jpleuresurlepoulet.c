/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jpleuresurlepoulet.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:23:27 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/17 18:24:04 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!map || !map[y])
		return ;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'P' || map[y][x] == '1')
				print_img(data->img[1].img, x, y, data);
			x++;
		}
		y++;
	}
}

int	initiate(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (perror("Error\nFailure initiating mlx."), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "Cub3D");
	if (!data->win_ptr)
		return (perror("Error\nFailure initiating window"), 1);
	return (0);
}
