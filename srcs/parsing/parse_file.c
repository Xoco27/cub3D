/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:53 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/04 15:31:15 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	data->mapinfo.file = make_tab(av, &data->mapinfo.line_count);
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

