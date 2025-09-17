/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:48:38 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/17 17:54:21 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map.file)
	{
		i = 0;
		while (data->map.file[i])
			free(data->map.file[i++]);
		free(data->map.file);
		data->map.file = NULL;
	}
	if (data->texture.north)
		free(data->texture.north);
	if (data->texture.south)
		free(data->texture.south);
	if (data->texture.east)
		free(data->texture.east);
	if (data->texture.west)
		free(data->texture.west);
}

int	error_message(t_data *data, char *detail, char *str)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	free_all(data);
	exit(EXIT_FAILURE);
}
