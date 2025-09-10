/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:42:36 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/10 17:32:55 by cfleuret         ###   ########.fr       */
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
			data->player.angle = 354 * PI / 180;
	}
	if (keysym == XK_Right)
	{
		data->player.angle += 6 * PI / 180;
		if (data->player.angle > 360 * PI / 180)
			data->player.angle = 6 * PI / 180;
	}
}

int	mouse(int x, int y, t_data *data)
{
	double		sensitivity;
	int			dx;
	double		half_x;
	double		half_y;

	half_x = data->win_width / 2;
	half_y = data->win_height / 2;
	(void)y;
	sensitivity = 0.001;
	dx = x - half_x;
	data->player.angle += dx * sensitivity;
	if (data->player.angle < 0)
		data->player.angle = 360 * PI / 180;
	else if (data->player.angle > 2 * PI)
		data->player.angle = 0 * PI / 180;

	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		half_x, half_y);
	return (0);
}


void	update_pos(t_data *data, int keysym)
{
	if ((keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		&& data->player.next_y >= 0 && data->player.next_y < data->map.height
		&& data->player.next_x >= 0 && data->player.next_x < data->map.width
		&& (data->map.file[(int)(data->player.next_y + 0.2)]
		[(int)(data->player.next_x + 0.2)] != '1')
		&& (data->map.file[(int)(data->player.next_y - 0.2)]
		[(int)(data->player.next_x - 0.2)] != '1'))
	{
		data->player.pos_x = data->player.next_x;
		data->player.pos_y = data->player.next_y;
	}
}
