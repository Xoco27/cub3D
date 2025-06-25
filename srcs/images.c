/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 16:41:28 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_filename(char *filename)
{
	int	len;

	len = strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", len) != 0)
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
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_down.xpm", &data->img.width, &data->img.height);
	print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.wall);
	mlx_destroy_image(data->mlx_ptr, data->player.down);
}
