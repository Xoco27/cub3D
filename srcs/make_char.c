/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:00:15 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/27 17:12:31 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pos(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P' /*|| map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W'*/)
			{
				data->player.pos_x = x;
				data->player.pos_y = y;
				return ;
			}
			x++;
		}
		y++;
		data->player.vector_x = 0;
		data->player.vector_y = 1;
	}
}
