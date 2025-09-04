/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:44 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/04 14:11:29 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_win(t_data *data)
{
	data->win_height = 800;
	data->win_width = 1220;
}

int	on_destroy(t_data *data)
{
	destroy(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map(data->tab);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	int		i;

	i = 0;
	data->player.dir_x = cos(data->player.angle);
	data->player.dir_y = sin(data->player.angle);
	data->player.side_x = -sin(data->player.angle);
	data->player.side_y = cos(data->player.angle);
	data->player.next_x = data->player.pos_x;
	data->player.next_y = data->player.pos_y;
	moving(data, keysym);
	data->map.map_x = (int)data->player.next_x;
	data->map.map_y = (int)data->player.next_y;
	update_pos(data, keysym);
	if (keysym == XK_Escape)
		on_destroy(data);
	return (0);
}

void	hook(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render, data);
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
	data.tab = make_tab(data.tab, argv);
	if (data.tab == NULL)
		return (perror("Error\nEmpty map"), 1);
	if (!data.tab)
		return (perror("Error\nMap making failed."), 1);
	set_win(&data);
	if (initiate(&data) == 1)
		return (perror("Error\nFailed to initiate data or window"), 1);
	create_images(&data);
	hook(&data);
	free_map(data.tab);
	return (0);
}
