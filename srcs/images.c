/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/04 15:16:11 by cfleuret         ###   ########.fr       */
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
	int	j;

	i = 0;
	data->map.width = 0;
	while (data->tab[i])
		i++;
	data->map.height = i;
	j = 0;
	while (data->tab[j])
	{
		while (data->tab[j][i])
			i++;
		if (i > data->map.width)
			data->map.width = i;
		j++;
	}
	data->player.width = TILE;
	data->player.height = TILE;
	pos(data->map, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->assets = malloc(sizeof(char *) * 5);
	data->assets[0] = ft_strdup("assets/wall.xpm");
	data->assets[1] = ft_strdup("assets/floor.xpm");
	data->assets[2] = ft_strdup("assets/door_closed.xpm");
	data->assets[3] = ft_strdup("assets/door_opened.xpm");
	init_img(data, data->img);
	// data->map.floor = mlx_xpm_file_to_image(data->mlx_ptr,
	// 		"assets/floor.xpm", &data->player.width, &data->player.height);
	// data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,
	// 		"assets/link_down.xpm", &data->player.width, &data->player.height);
	//print_map((*data).map, data);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i != 4)
			free(data->assets[i]);
		mlx_destroy_image(data->mlx_ptr, data->img[i].img);
		i++;
	}
	free(data->assets);
}
