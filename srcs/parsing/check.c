/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:08:57 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/08 20:36:11 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_map(t_data *data)
{
	int	i;

	i = 0;
	if (!(data->mapinfo.file))
		return (error_message(*data->mapinfo.file, ERR_MAP_MISSING));
	if (!validate_walls(data->mapinfo.file, i))
		return (error_message(*data->mapinfo.file, ERR_WALL_INVALID));
	i = 0;
	if (!validate_player_position(data->mapinfo.file, i))
		return (error_message(*data->mapinfo.file, ERR_PLAYER_POS));
	if (!validate_elements(data->mapinfo.file))
		(error_message(*data->mapinfo.file, ERR_ELEMENT));
	return (0);
}

int	parse_args(t_data *data, char **av)
{
	if (check_filename(av[1], true) == 1)
		return (perror("Error\nWrong file extension"), 1);
	parse_map(data, av[1]);
	validate_map(data);
	return (0);
}
