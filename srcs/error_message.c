/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:48:38 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/08/26 17:07:58 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error_message(char *detail, char *str)
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
	return (1);
}
