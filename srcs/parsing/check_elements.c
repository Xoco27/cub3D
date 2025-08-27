/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:24 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/08/27 18:09:56 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_texture_line(char *line)
{
	return (
		ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0
	);
}

static int	is_color_line(char *line)
{
	return (
		ft_strncmp(line, "F ", 2) == 0 ||
		ft_strncmp(line, "C ", 2) == 0
	);
}

static int	is_map_line(char *line)
{
	int	i = 0;

	while (line[i])
	{
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
		if (is_map_line(file[i]))
			break ;
		if (is_texture_line(file[i]))
			textures++;
		else if (is_color_line(file[i]))
			colors++;
		else if (file[i][0] == '\0')
			;
		else
			return (false);
		i++;
	}
	printf("%d, %d\n", colors, textures);
	if (textures != 4 || colors != 2)
		return (false);
	if (!file[i] || !is_map_line(file[i]))
		return (false);
	return (true);
}
