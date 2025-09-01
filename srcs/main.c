/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:44 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/01 18:25:22 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_win(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->tab[y])
		y++;
	x = ft_strlen(data->tab[0]);
	data->win_height = y * TILE;
	data->win_width = x * TILE;
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
	double	next_x;
	double	next_y;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	int		i;

	i = 0;
	dir_x = cos(data->player.angle);
	dir_y = sin(data->player.angle);
	side_x = -sin(data->player.angle);
	side_y = cos(data->player.angle);
	next_x = data->player.pos_x;
	next_y = data->player.pos_y;
	if (keysym == XK_w)
	{
		next_x += dir_x * SPEED;
		next_y += dir_y * SPEED;
	}
	if (keysym == XK_s)
	{
		next_x -= dir_x * SPEED;
		next_y -= dir_y * SPEED;
	}
	if (keysym == XK_d)
	{
		next_x += side_x * SPEED;
		next_y += side_y * SPEED;
	}
	if (keysym == XK_a)
	{
		next_x -= side_x * SPEED;
		next_y -= side_y * SPEED;
	}
	if (keysym == XK_Left || keysym == XK_Right)
		rotate(data, keysym);
	data->map.map_x = (int)next_x;
	data->map.map_y = (int)next_y;
	update_pos(data, next_x, next_y, keysym);
	init_img(data, &data->img, 0);
	//print_map(data->tab, data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw_floor_and_sky(data);
	ray_cast(data, i);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
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
