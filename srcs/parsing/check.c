/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:08:57 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/17 18:16:28 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_map(t_data *data)
{
	int	i;

	i = 0;
	if (!(data->map.file))
		return (error_message(data, *data->map.file, ERR_MAP_MISSING));
	if (!validate_walls(data->map.file, i))
		return (error_message(data, *data->map.file, ERR_WALL_INVALID));
	if (!validate_player_position(data->map.file))
		return (error_message(data, *data->map.file, ERR_PLAYER_POS));
	if (!validate_elements(data->map.file))
		(error_message(data, *data->map.file, ERR_ELEMENT));
	return (0);
}

int	parse_args(t_data *data, char **av)
{
	if (check_filename(data, av[1], true) == 1)
		return (perror("Error\nWrong file extension"), 1);
	parse_map(data, av[1]);
	validate_map(data);
	return (0);
}
