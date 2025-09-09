/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:24 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/09 16:46:16 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_texture_line(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	return (
		ft_strncmp(line + j, "NO ", 3) == 0
		|| ft_strncmp(line + j, "SO ", 3) == 0
		|| ft_strncmp(line + j, "WE ", 3) == 0
		|| ft_strncmp(line + j, "EA ", 3) == 0
	);
	return (1);
}

static int	is_color_line(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	return (
		ft_strncmp(line + j, "F ", 2) == 0
		|| ft_strncmp(line + j, "C ", 2) == 0
	);
}

static int	is_map_liner(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (*line == 'F' || *line == 'C' || *line == '\0')
			return (0);
		if (line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	validate_elements(char **file)
{
	int	i;
	int	textures;
	int	colors;

	i = 0;
	textures = 0;
	colors = 0;
	while (file[i])
	{
		if (is_map_liner(file[i]))
			break ;
		if (is_texture_line(file[i]))
			textures++;
		else if (is_color_line(file[i]))
			colors++;
		else if (file[i][0] == '\0' || file[i][0] == '\n')
			;
		i++;
	}
	if (textures != 4 || colors != 2)
		return (false);
	if (!file[i] || !is_map_liner(file[i]))
		return (false);
	return (true);
}
