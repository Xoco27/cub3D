/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 13:36:11 by cfleuret         ###   ########.fr       */
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
	while (data->tab[i])
		i++;
	data->map.height = i;
	i = 0;
	while (data->tab[0][i])
		i++;
	data->map.width = i;
	data->player.width = TILE;
	data->player.height = TILE;
	pos((*data).tab, data);
}

void	create_images(t_data *data)
{
	wh(data);
	init_img(data, &data->img, 0);
	init_img(data, &data->wall, 1);
	data->map.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/floor.xpm", &data->player.width, &data->player.height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_down.xpm", &data->player.width, &data->player.height);
	//print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->map.wall);
	mlx_destroy_image(data->mlx_ptr, data->player.down);
}
