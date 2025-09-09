/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:42:36 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/09 13:00:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	moving(t_data *data, int keysym)
{
	if (keysym == XK_w)
	{
		data->player.next_x += data->player.dir_x * SPEED;
		data->player.next_y += data->player.dir_y * SPEED;
	}
	if (keysym == XK_s)
	{
		data->player.next_x -= data->player.dir_x * SPEED;
		data->player.next_y -= data->player.dir_y * SPEED;
	}
	if (keysym == XK_d)
	{
		data->player.next_x += data->player.side_x * SPEED;
		data->player.next_y += data->player.side_y * SPEED;
	}
	if (keysym == XK_a)
	{
		data->player.next_x -= data->player.side_x * SPEED;
		data->player.next_y -= data->player.side_y * SPEED;
	}
	if (keysym == XK_Left || keysym == XK_Right)
		rotate(data, keysym);
}

void	rotate(t_data *data, int keysym)
{
	if (keysym == XK_Left)
	{
		data->player.angle -= 6 * PI / 180;
		if (data->player.angle < 0)
			data->player.angle = 360 * PI / 180;
	}
	if (keysym == XK_Right)
	{
		data->player.angle += 6 * PI / 180;
		if (data->player.angle > 360 * PI / 180)
			data->player.angle = 0;
	}
}

void	update_pos(t_data *data, int keysym)
{
	if ((keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		&& data->player.next_y >= 0 && data->player.next_y < data->map.height
		&& data->player.next_x >= 0 && data->player.next_x < data->map.width
		&& (data->tab[(int)(data->player.next_y + 0.2)]
		[(int)(data->player.next_x + 0.2)] != '1')
		&& (data->tab[(int)(data->player.next_y - 0.2)]
		[(int)(data->player.next_x - 0.2)] != '1'))
	{
		data->player.pos_x = data->player.next_x;
		data->player.pos_y = data->player.next_y;
	}
}
