/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:43:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/09 18:56:21 by cfleuret         ###   ########.fr       */
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

int	check_filename(t_data *data, char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (error_message(data, arg, ERR_INVALID_FILENAME));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error_message(data, arg, strerror(errno)));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (error_message(data, arg, ERR_INVALID_FILENAME));
	if (!cub && !is_xpm_file(arg))
		return (error_message(data, arg, ERR_INVALID_FILENAME));
	return (0);
}

void	wh(t_data *data)
{
	int	i;
	int	j;

	data->map.width = 0;
	j = 0;
	while (data->tab[j])
	{
		i = 0;
		while (data->tab[j][i])
			i++;
		if (i > data->map.width)
			data->map.width = i;
		j++;
	}
	data->map.height = j;
	data->player.width = TILE;
	data->player.height = TILE;
	pos(data->tab, data);
}

void	create_images(t_data *data)
{
	wh(data);
	data->assets = malloc(sizeof(char *) * 5);
	data->assets[0] = ft_strdup(data->texture.north);
	data->assets[1] = ft_strdup(data->texture.south);
	data->assets[2] = ft_strdup(data->texture.east);
	data->assets[3] = ft_strdup(data->texture.west);
	init_img(data, data->img);
}
