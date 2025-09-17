/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:17:51 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/17 17:56:21 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	error(char **map)
{
	free(map);
	perror("Error\nCan't open file.");
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
	if (data->tab)
	{
		free_map(data->tab);
		data->tab = NULL;
	}
	if (data->map.file)
	{
		free_map(data->map.file);
		data->map.file = NULL;
	}
	free(data->assets);
	free(data->texture.east);
	free(data->texture.south);
	free(data->texture.west);
	free(data->texture.north);
}
