/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:32:23 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/09 17:01:46 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	parse_rgb(int dst[3], char *str)
{
	char	**split;
	int		i;
	int		val;

	split = ft_split(str, ',');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (ft_free_split(split), 1);
	i = 0;
	while (i < 3)
	{
		if (split[i][0] == '\0')
			return (ft_free_split(split), 1);
		val = ft_atoi(split[i]);
		if (val < 0 || val > 255)
			return (ft_free_split(split), 1);
		dst[i] = val;
		i++;
	}
	ft_free_split(split);
	return (0);
}

int	fill_color_textures(t_texture *tex, char *line, int j)
{
	char	*value;

	if (ft_strncmp(line + j, "F", 1) == 0)
	{
		value = ft_strtrim(line + j + 1, " \t\n");
		if (!value || parse_rgb(tex->color.floor, value))
			return (free(value), 1);
		free(value);
		tex->color.has_floor = 1;
		printf("%d %d %d\n", tex->color.floor[0], tex->color.floor[1], tex->color.floor[2]);
		return (0);
	}
	else if (ft_strncmp(line + j, "C", 1) == 0)
	{
		value = ft_strtrim(line + j + 1, " \t\n");
		if (!value || parse_rgb(tex->color.ceiling, value))
			return (free(value), 1);
		free(value);
		tex->color.has_ceiling = 1;
		printf("%d %d %d\n", tex->color.ceiling[0], tex->color.ceiling[1], tex->color.ceiling[2]);
		return (0);
	}
	if (is_texture_line(line))
		return (0);
	return (1);
}

