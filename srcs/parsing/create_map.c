/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:23:48 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/08/28 15:28:28 by mgarsaul         ###   ########.fr       */
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

int	create_map(t_data *data, char **map)
{
	int		i;
	int		k;
	int		height;

	i = 0;
	while (map[i] && !is_map_line(map[i]))
		i++;
	if (!map[i])
		return (1);
	height = map_height(map, i);
	if (height == 0)
		return (1);
	data->map = malloc(sizeof(char *) * (height + 1));
	if (!data->map)
		return (1);
	k = 0;
	while (map[i] && is_map_line(map[i]))
	{
		data->map[k] = strdup(map[i]);
		if (!data->map[k])
		{
			while (k > 0)
				free(data->map[--k]);
			free(data->map);
			return (1);
		}
		k++;
		i++;
	}
	data->map[k] = NULL;
	return (0);
}
