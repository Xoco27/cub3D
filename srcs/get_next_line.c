/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:35:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:08:45 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	create_stash(t_list **stash, char *buffer)
{
	int		i;
	t_list	*n;
	char	*p;

	i = 0;
	while (buffer[i])
	{
		p = malloc(1);
		if (p == NULL)
			return (-1);
		*p = buffer[i];
		n = ft_lstnew(p);
		if (n == NULL)
			free(p);
		if (n == NULL)
			return (-1);
		ft_lstadd_back(stash, n);
		i++;
	}
	return (0);
}

static void	create(int fd, t_list **stash)
{
	int		j;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return ;
	while (1)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		if (j <= 0)
			break ;
		buffer[j] = '\0';
		if (create_stash(stash, buffer) == -1)
		{
			ft_lstclear(stash, free);
			break ;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
}

static char	*create_line(int i, t_list **stash, int len)
{
	t_list	*temp;
	char	*line;

	temp = *stash;
	while (temp && *(char *)temp->content != '\n')
	{
		len++;
		temp = temp->next;
	}
	if (temp && *(char *)temp->content == '\n')
		len++;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	temp = *stash;
	while (temp && i < len)
	{
		line[i++] = *(char *)temp->content;
		*stash = (*stash)->next;
		free(temp->content);
		free(temp);
		temp = *stash;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				i;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&stash, free);
		return (NULL);
	}
	i = 0;
	len = 0;
	create(fd, &stash);
	if (!stash)
		return (NULL);
	line = create_line(i, &stash, len);
	if (line == NULL || stash == NULL)
	{
		ft_lstclear(&stash, free);
		stash = NULL;
	}
	return (line);
}
