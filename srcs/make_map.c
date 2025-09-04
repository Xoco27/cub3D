/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:48:22 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 15:04:21 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**make_tab(char *filepath, int *line_count)
{
	char	*txt;
	int		fd;
	int		i;
	char	**map;

	i = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nError opening file"), NULL);
	txt = get_next_line(fd);
	while (txt)
	{
		i++;
		free(txt);
		txt = get_next_line(fd);
	}
	close(fd);
	if (i == 0)
		return (perror("Error\nEmpty map file"), NULL);
	*line_count = i;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nError reopening file"), NULL);
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (perror("Error\nMalloc failed"), NULL);
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

void	print_map(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!map || !map[y])
		return ;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'P')
				print_img(data->img.floor, x, y, data);
			if (map[y][x] == '1')
				print_img(data->img.wall, x, y, data);
			x++;
		}
		y++;
	}
}

int	initiate(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (perror("Error\nFailure initiating mlx."), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "Cub3D");
	if (!data->win_ptr)
		return (perror("Error\nFailure initiating window"), 1);
	return (0);
}
