/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:48:22 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/17 18:23:54 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_lines_in_file(char *filepath)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static char	**alloc_map(int lines)
{
	char	**map;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
	{
		perror("Error\nMalloc failed");
		return (NULL);
	}
	return (map);
}

char	**make_tab(char *filepath, int *line_count)
{
	int		lines;
	char	**map;

	lines = count_lines_in_file(filepath);
	if (lines < 0)
		return (perror("Error\nError opening file"), NULL);
	if (lines == 0)
		return (perror("Error\nEmpty map file"), NULL);
	*line_count = lines;
	map = alloc_map(lines);
	if (!map)
		return (NULL);
	return (fill_rows(map, filepath));
}

char	**fill_rows(char **map, char *filepath)
{
	char	*txt;
	int		fd;
	int		i;

	i = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		error(map);
	txt = get_next_line(fd);
	while (txt)
	{
		clean_line(txt);
		map[i] = ft_strdup(txt);
		free(txt);
		if (!map[i])
		{
			close(fd);
			return (free_map(map), NULL);
		}
		txt = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	print_img(void *img, int x, int y, t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, img, x * TILE, y * TILE);
}
