/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 15:04:22 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	check_filename(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (error_message(arg, "tg"));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error_message(arg, strerror(errno)));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (error_message(arg, "tg"));
	if (!cub && !is_xpm_file(arg))
		return (error_message(arg, "tg"));
	return (0);
}

void	wh(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	data->img.height = i;
	i = 0;
	while (data->map[0][i])
		i++;
	data->img.width = i;
	data->player.width = TILE;
	data->player.height = TILE;
	pos(data->map, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->img.wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/wall.xpm", &data->img.width, &data->img.height);
	data->img.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/floor.xpm", &data->img.width, &data->img.height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/link_down.xpm", &data->img.width, &data->img.height);
	print_map(data->map, data);
	print_player(data->player.down, data->player.pos_x,
		data->player.pos_y, data);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.wall);
	mlx_destroy_image(data->mlx_ptr, data->player.down);
}
