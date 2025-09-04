/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/04 13:11:35 by cfleuret         ###   ########.fr       */
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
	int	j;

	i = 0;
	data->map.width = 0;
	while (data->tab[i])
		i++;
	data->map.height = i;
	j = 0;
	while (data->tab[j])
	{
		while (data->tab[j][i])
			i++;
		if (i > data->map.width)
			data->map.width = i;
		j++;
	}
	data->player.width = TILE;
	data->player.height = TILE;
	pos((*data).tab, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->assets = malloc(sizeof(char *) * 5);
	data->assets[0] = ft_strdup("assets/wall.xpm");
	data->assets[1] = ft_strdup("assets/floor.xpm");
	data->assets[2] = ft_strdup("assets/door_closed.xpm");
	data->assets[3] = ft_strdup("assets/door_opened.xpm");
	init_img(data, data->img);
	// data->map.floor = mlx_xpm_file_to_image(data->mlx_ptr,
	// 		"assets/floor.xpm", &data->player.width, &data->player.height);
	// data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
	// 		"assets/link_down.xpm", &data->player.width, &data->player.height);
	//print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i != 4)
			free(data->assets[i]);
		mlx_destroy_image(data->mlx_ptr, data->img[i].img);
		i++;
	}
	free(data->assets);
}
