/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_file_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:40:57 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/08 19:24:37 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// static char	*get_texture_path(char *line, int j)
// {
// 	int		len;
// 	int		i;
// 	char	*path;

// 	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
// 		j++;
// 	len = j;
// 	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
// 		len++;
// 	path = malloc(sizeof(char) * (len - j + 1));
// 	if (!path)
// 		return (NULL);
// 	i = 0;
// 	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
// 		path[i++] = line[j++];
// 	path[i] = '\0';
// 	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
// 		j++;
// 	if (line[j] && line[j] != '\n')
// 	{
// 		free(path);
// 		path = NULL;
// 	}
// 	return (path);
// }

// static int	fill_direction_textures(t_texture *textures, char *line, int j)
// {
// 	if (line[j + 2] && ft_isprint(line[j + 2]))
// 		return (1);
// 	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->north))
// 		textures->north = get_texture_path(line, j + 2);
// 	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->south))
// 		textures->south = get_texture_path(line, j + 2);
// 	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->west))
// 		textures->west = get_texture_path(line, j + 2);
// 	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->east))
// 		textures->east = get_texture_path(line, j + 2);
// 	else
// 		return (1);
// 	return (0);
// }

int	fill_direction_textures(t_texture *tex, char *line, int j)
{
	char	*path;

	if (ft_strncmp(line + j, "NO", 2) == 0 && (line[j + 2] == ' ' || line[j + 2] == '\t'))
	{
		path = ft_strtrim(line + j + 2, " \t\n");
		if (!path)
			return (1);
		tex->north = path;
		return (0);
	}
	else if (ft_strncmp(line + j, "SO", 2) == 0 && (line[j + 2] == ' ' || line[j + 2] == '\t'))
	{
		path = ft_strtrim(line + j + 2, " \t\n");
		if (!path)
			return (1);
		tex->south = path;
		return (0);
	}
	else if (ft_strncmp(line + j, "WE", 2) == 0 && (line[j + 2] == ' ' || line[j + 2] == '\t'))
	{
		path = ft_strtrim(line + j + 2, " \t\n");
		if (!path)
			return (1);
		tex->west = path;
		return (0);
	}
	else if (ft_strncmp(line + j, "EA", 2) == 0 && (line[j + 2] == ' ' || line[j + 2] == '\t'))
	{
		path = ft_strtrim(line + j + 2, " \t\n");
		if (!path)
			return (1);
		tex->east = path;
		return (0);
	}
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
				return (error_message(map[i], ERR_TEXTURE_INVALID));
			return (2);
		}
		else
		{
			if (fill_color_textures(&data->texture, map[i], j) == 1)
				return (error_message(map[i], ERR_TEXTURE_INVALID));
			return (2);
		}
	}
	return (0);
}

int	verify_file_data(t_data *data, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		get_into_file(data, map, i);
		if (is_map_line(map[i]))
			create_map(data, map);
		i++;
	}
	return (0);
}
