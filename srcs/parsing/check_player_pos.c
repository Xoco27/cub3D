/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:48:40 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/17 18:16:08 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_player(t_pos *p, int *player_count)
{
	(*player_count)++;
	if (p->i == p->start || !p->file[p->i + 1]
		|| p->j == 0 || !p->file[p->i][p->j + 1]
		|| p->file[p->i - 1][p->j] == ' ' || p->file[p->i + 1][p->j] == ' '
		|| p->file[p->i][p->j - 1] == ' ' || p->file[p->i][p->j + 1] == ' ')
		return (0);
	return (1);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\n'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	process_map_char(t_pos *p, int *player_count)
{
	char	c;

	c = p->file[p->i][p->j];
	if (is_player_char(c))
	{
		if (!check_player(p, player_count))
			return (0);
	}
	else if (!is_valid_char(c))
		return (0);
	return (1);
}

int	validate_player_position(char **file)
{
	t_pos	p;
	int		j;
	int		player_count;

	player_count = 0;
	p.start = 0;
	while (file[p.start] && !is_map_line(file[p.start]))
		p.start++;
	if (!file[p.start])
		return (0);
	p.i = p.start;
	while (file[p.i])
	{
		j = 0;
		while (file[p.i][j])
		{
			p.file = file;
			p.j = j;
			if (!process_map_char(&p, &player_count))
				return (0);
			j++;
		}
		p.i++;
	}
	return (player_count == 1);
}
