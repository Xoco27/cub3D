/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_file_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:40:57 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/18 14:53:27 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_texture_path(char **dest, char *line, int j, int skip)
{
	char	*path;
	int		fd;
	int		dir_fd;

	if (line[j + skip] != ' ' && line[j + skip] != '\t')
		return (1);
	path = ft_strtrim(line + j + skip, " \t\n");
	if (!path)
		return (1);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
		return (free(path), 1);
	dir_fd = open(path, O_DIRECTORY);
	if (dir_fd != -1)
	{
		close(dir_fd);
		free(path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(path), 1);
	close(fd);
	*dest = path;
	return (0);
}

static int	fill_direction_textures(t_texture *tex,
	char *line, int j)
{
	if (ft_strncmp(line + j, "NO", 2) == 0)
		return (set_texture_path(&tex->north, line, j, 2));
	else if (ft_strncmp(line + j, "SO", 2) == 0)
		return (set_texture_path(&tex->south, line, j, 2));
	else if (ft_strncmp(line + j, "WE", 2) == 0)
		return (set_texture_path(&tex->west, line, j, 2));
	else if (ft_strncmp(line + j, "EA", 2) == 0)
		return (set_texture_path(&tex->east, line, j, 2));
	else if (ft_strncmp(line + j, "F", 1) == 0
		|| ft_strncmp(line + j, "C", 1) == 0)
		return (0);
	return (1);
}

static int	get_into_file(t_data *data, char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			if (fill_direction_textures(&data->texture, map[i], j) == 1)
				return (error_message(data, map[i], ERR_TEXTURE_INVALID));
			else
			{
				if (fill_color_textures(&data->texture, map[i], j) == 1)
					return (error_message(data, map[i], ERR_COLOR_INVALID));
			}
		}
	}
	return (0);
}

int	verify_file_data(t_data *data, char **map)
{
	int	i;
	int	ret;

	data->texture.north = NULL;
	data->texture.south = NULL;
	data->texture.east = NULL;
	data->texture.west = NULL;
	data->tab = NULL;
	i = 0;
	while (map[i])
	{
		free_map(data->tab);
		ret = get_into_file(data, map, i);
		if (ret != 0)
			return (1);
		if (is_map_line(map[i]))
		{
			ret = create_map(data, map);
			if (ret != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
