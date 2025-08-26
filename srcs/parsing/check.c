/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:08:57 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/26 18:29:21 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_rect(char	**map)
{
	int		y;
	size_t	len;

	len = 0;
	y = 1;
	len = ft_strlen(map[0]) - 1;
	while (map[y])
	{
		if (ft_strlen(map[y]) - 1 != len)
			return (0);
		y++;
	}
	return (1);
}

int	check_map(t_data *data)
{
	if (!(data->mapinfo.file))
		return (error_message(*data->map, ERR_MAP_MISSING));
	// if (!validate_walls(data))
	// 	return (error_message(*data->map, ERR_WALL_INVALID));
	// if (!validate_player_position(data))
	// 	return (error_message(*data->map, ERR_PLAYER_POS));
	return (0);
}

int	parse_args(t_data *data, char **av)
{
	if (check_filename(av[1], true) == 1)
		return (perror("Error\nWrong file extension"), 1);
	parse_map(data, av[1]);
	check_map(data);
	// check_texture(data);
	return (0);
}
