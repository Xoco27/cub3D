/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 12:51:00 by cfleuret         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	data->img.height = i;
	i = 0;
	while (data->map[0][i])
		i++;
	data->img.width = i;
	data->player.width = TILE;
	data->player.height = TILE;
	pos((*data).map, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->img.wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/wall.xpm", &data->player.width, &data->player.height);
	data->img.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/floor.xpm", &data->player.width, &data->player.height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_down.xpm", &data->player.width, &data->player.height);
	//print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.wall);
	mlx_destroy_image(data->mlx_ptr, data->player.down);
}
