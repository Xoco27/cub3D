/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:08:47 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_filename(char *filename)
{
	int	len;

	len = strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".ber", len) != 0)
		return (1);
	return (0);
}

void	wh(t_data *data)
{
	data->img.width = TILE;
	data->img.height = TILE;
	data->player.width = TILE;
	data->player.height = TILE;
	pos((*data).map, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->img.wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/wall.xpm", &data->img.width, &data->img.height);
	data->img.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/floor.xpm", &data->img.width, &data->img.height);
	data->img.exit_closed = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/door_closed.xpm", &data->img.width, &data->img.height);
	data->img.exit_opened = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/door_opened.xpm", &data->img.width, &data->img.height);
	data->img.item = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/item.xpm", &data->img.width, &data->img.height);
	data->player.up = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_up.xpm", &data->player.width, &data->player.height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_down.xpm", &data->player.width, &data->player.height);
	data->player.right = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_right.xpm", &data->player.width, &data->player.height);
	data->player.left = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_left.xpm", &data->player.width, &data->player.height);
	print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.wall);
	mlx_destroy_image(data->mlx_ptr, data->img.floor);
	mlx_destroy_image(data->mlx_ptr, data->img.exit_closed);
	mlx_destroy_image(data->mlx_ptr, data->img.exit_opened);
	mlx_destroy_image(data->mlx_ptr, data->img.item);
	mlx_destroy_image(data->mlx_ptr, data->player.up);
	mlx_destroy_image(data->mlx_ptr, data->player.down);
	mlx_destroy_image(data->mlx_ptr, data->player.right);
	mlx_destroy_image(data->mlx_ptr, data->player.left);
}

int	non_valid(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'C'
					&& map[y][x] != 'E' && map[y][x] != 'P')
			{
				perror("Error\nInvalid character in the map.");
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
