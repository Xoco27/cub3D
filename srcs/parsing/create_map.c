/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:23:48 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/10 17:01:00 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	map_height(char **map, int i)
{
	int	count;

	count = 0;
	while (map[i] && is_map_line(map[i]))
	{
		count++;
		i++;
	}
	return (count);
}

static int	copy_map_lines(t_data *data, char **map, int i, int height)
{
	int	k;

	data->tab = malloc(sizeof(char *) * (height + 1));
	if (!data->tab)
		return (1);
	k = 0;
	while (map[i] && is_map_line(map[i]))
	{
		data->tab[k] = ft_strdup(map[i]);
		if (!data->tab[k])
		{
			free_map(data->tab);
			return (1);
		}
		k++;
		i++;
	}
	data->tab[k] = NULL;
	return (0);
}

int	create_map(t_data *data, char **map)
{
	int	i;
	int	height;

	i = 0;
	while (map[i] && !is_map_line(map[i]))
		i++;
	if (!map[i])
		return (1);
	height = map_height(map, i);
	if (height == 0)
		return (1);
	if (copy_map_lines(data, map, i, height))
		return (1);
	return (0);
}
