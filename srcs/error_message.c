/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:48:38 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/09/09 17:47:30 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (!data->map.file)
		return ;
	while (data->map.file[i])
	{
		free(data->map.file[i]);
		i++;
	}
	free(data->map.file);
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
