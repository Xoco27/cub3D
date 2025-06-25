/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:00:15 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:08:55 by cfleuret         ###   ########.fr       */
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
			if (map[y][x] == 'P')
			{
				data->player.pos_x = x;
				data->player.pos_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	down_char(char **map, t_data *data)
{
	if (map[data->player.pos_y + 1][data->player.pos_x] != '1'
			&& map[data->player.pos_y + 1][data->player.pos_x] != 'E'
			&& data->score != 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_y += 1;
		print_img(data->player.down, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
	if (map[data->player.pos_y + 1][data->player.pos_x] != '1'
			&& data->score == 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_y += 1;
		print_img(data->player.down, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
}

void	up_char(char **map, t_data *data)
{
	if (map[data->player.pos_y - 1][data->player.pos_x] != '1'
			&& map[data->player.pos_y - 1][data->player.pos_x] != 'E'
			&& data->score != 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_y -= 1;
		print_img(data->player.up, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
	if (map[data->player.pos_y - 1][data->player.pos_x] != '1'
			&& data->score == 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_y -= 1;
		print_img(data->player.up, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
}

void	right_char(char **map, t_data *data)
{
	if (map[data->player.pos_y][data->player.pos_x + 1] != '1'
			&& map[data->player.pos_y][data->player.pos_x + 1] != 'E'
			&& data->score != 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_x += 1;
		print_img(data->player.right, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
	if (map[data->player.pos_y][data->player.pos_x + 1] != '1'
			&& data->score == 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_x += 1;
		print_img(data->player.right, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
}

void	left_char(char **map, t_data *data)
{
	if (map[data->player.pos_y][data->player.pos_x - 1] != '1'
			&& map[data->player.pos_y][data->player.pos_x - 1] != 'E'
			&& data->score != 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_x -= 1;
		print_img(data->player.left, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
	if (map[data->player.pos_y][data->player.pos_x - 1] != '1'
			&& data->score == 0)
	{
		print_img(data->img.floor, data->player.pos_x,
			data->player.pos_y, data);
		data->player.pos_x -= 1;
		print_img(data->player.left, data->player.pos_x,
			data->player.pos_y, data);
		data->move++;
		score(data);
		ft_exit(data);
	}
}
