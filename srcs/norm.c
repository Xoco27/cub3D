/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:26:38 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 17:01:14 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_pos(t_data *data, double next_x, double next_y, int keysym)
{
	if ((keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		&& next_y >= 0 && next_y < data->map.height
		&& next_x >= 0 && next_x < data->map.width
		&& data->tab[(int)next_y][(int)next_x] != '1')
	{
		data->player.pos_x = next_x;
		data->player.pos_y = next_y;
		//print_map(data->tab, data);
	}
}
