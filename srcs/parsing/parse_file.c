/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:53 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/10 15:34:25 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill_tab(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map.fd);
	while (line != NULL)
	{
		data->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map.file[row])
		{
			error_message(data, NULL, ERR_MALLOC);
			return (free_tab((void **)data->map.file));
		}
		while (line[i] != '\0')
			data->map.file[row][column++] = line[i++];
		data->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map.fd);
	}
	data->map.file[row] = NULL;
}

void	parse_map(t_data *data, char *av)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	data->map.file = make_tab(av, &data->map.line_count);
	data->map.path = av;
	if (!(data->map.file))
	{
		error_message(data, NULL, ERR_MALLOC);
		return ;
	}
	data->map.fd = open(av, O_RDONLY);
	if (data->map.fd < 0)
		error_message(data, av, strerror(errno));
	else
	{
		//fill_tab(row, column, i, data);
		close(data->map.fd);
	}
}
