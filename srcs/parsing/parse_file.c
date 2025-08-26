/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:53 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/08/26 18:35:52 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_line(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_message(path, strerror(errno));
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	fill_tab(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->mapinfo.fd);
	while (line != NULL)
	{
		data->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->mapinfo.file[row])
		{
			error_message(NULL, ERR_MALLOC);
			return (free_tab((void **)data->mapinfo.file));
		}
		while (line[i] != '\0')
			data->mapinfo.file[row][column++] = line[i++];
		data->mapinfo.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->mapinfo.fd);
	}
	data->mapinfo.file[row] = NULL;
}

void	parse_map(t_data *data, char *av)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	data->mapinfo.file = ft_calloc(data->mapinfo.line_count \
			+ 1, sizeof(char *));
	data->mapinfo.line_count = get_line(av);
	data->mapinfo.path = av;
	if (!(data->mapinfo.file))
	{
		error_message(NULL, ERR_MALLOC);
		return ;
	}
	data->mapinfo.fd = open(av, O_RDONLY);
	if (data->mapinfo.fd < 0)
		error_message(av, strerror(errno));
	else
	{
		fill_tab(row, column, i, data);
		close(data->mapinfo.fd);
	}
}
