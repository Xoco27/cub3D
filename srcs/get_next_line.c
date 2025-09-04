/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:35:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/28 12:54:03 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_free(char *txt, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(txt, buffer);
	free(txt);
	return (temp);
}

char	*read_first_line(int fd, char *txt)
{
	char	*buffer;
	int		bytes_read;

	if (!txt)
		txt = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (txt);
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		txt = ft_free(txt, buffer);
		if (ft_strchr(txt, '\n'))
			break ;
	}
	free (buffer);
	return (txt);
}

char	*get_the_line(char *txt)
{
	int		i;
	char	*str;

	i = 0;
	if (!txt[i])
		return (NULL);
	while (txt[i] && txt[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (txt[i] && txt[i] != '\n')
	{
		str[i] = txt[i];
		i++;
	}
	if (txt[i] && txt[i] == '\n')
		str[i++] = '\n';
	return (str);
}

char	*clean_first_line(char *txt)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (txt[i] && txt[i] != '\n')
		i++;
	if (!txt[i])
	{
		free (txt);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(txt) - i + 1), sizeof(*txt));
	if (!str)
		return (NULL);
	while (txt[++i])
		str[j++] = txt[i];
	str[j] = '\0';
	free (txt);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*output;
	static char	*txt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	txt = read_first_line(fd, txt);
	if (!txt)
		return (NULL);
	output = get_the_line(txt);
	txt = clean_first_line(txt);
	return (output);
}
