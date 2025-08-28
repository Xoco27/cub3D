/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:44 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 13:21:55 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_win(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
		y++;
	x = ft_strlen(data->map[0]);
	data->win_height = y * TILE;
	data->win_width = x * TILE;
}

int	on_destroy(t_data *data)
{
	destroy(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map(data->map);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	double	next_x;
	double	next_y;
	int		i;

	i = 0;
	next_x = data->player.pos_x;
	next_y = data->player.pos_y;
	if (keysym == XK_w)
		next_y -= SPEED;
	if (keysym == XK_s)
		next_y += SPEED;
	if (keysym == XK_a)
		next_x -= SPEED;
	if (keysym == XK_d)
		next_x += SPEED;
	if (keysym == XK_Left || keysym == XK_Right)
		rotate(data, keysym);
	data->img.map_x = (int)next_x;
	data->img.map_y = (int)next_y;
	update_pos(data, next_x, next_y, keysym);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	//print_map(data->map, data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ray_cast(data, i);
	if (keysym == XK_Escape)
		on_destroy(data);
	return (0);
}

void	hook(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		on_destroy, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (perror("Error\nNot enough or too much arguments."), 1);
	if (check_filename(argv[1]) == 1)
		return (perror("Error\nWrong file extension"), 1);
	data.move = 0;
	data.map = make_tab(data.map, argv);
	if (data.map == NULL)
		return (perror("Error\nEmpty map"), 1);
	if (!data.map)
		return (perror("Error\nMap making failed."), 1);
	set_win(&data);
	if (initiate(&data) == 1)
		return (perror("Error\nFailed to initiate data or window"), 1);
	create_images(&data);
	hook(&data);
	free_map(data.map);
	return (0);
}
