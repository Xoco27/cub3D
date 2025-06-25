/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:37 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/25 15:06:49 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# ifndef TILE
#  define TILE 128
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# include <fcntl.h>
# include <stdint.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_map
{
	void	*floor;
	void	*wall;
	void	*exit_closed;
	void	*exit_opened;
	void	*item;
	void	*spawn;
	int		width;
	int		height;
}		t_map;

typedef struct s_player
{
	void	*up;
	void	*down;
	void	*right;
	void	*left;
	int		width;
	int		height;
	int		pos_x;
	int		pos_y;
}		t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**copy;
	int			win_width;
	int			win_height;
	int			score;
	int			total;
	int			move;
	int			r;
	t_map		img;
	t_player	player;
}			t_data;

void	create_images(t_data *data);
char	*get_next_line(int fd);
void	free_map(char **map);
char	**make_tab(char **map, char **argv);
char	**fill_rows(char **map, char **argv);
void	print_img(void *img, int x, int y, t_data *data);
void	print_map(char **map, t_data *data);
int		check(char **map);
void	clean_line(char *line);
void	destroy(t_data *data);
int		check_es(char **map);
void	pos(char **map, t_data *data);
void	down_char(char **map, t_data *data);
void	up_char(char **map, t_data *data);
void	right_char(char **map, t_data *data);
void	left_char(char **map, t_data *data);
void	error(char **map);
void	score(t_data *data);
void	ft_exit(t_data *data);
int		is_map_valid(t_data *data);
int		another_check(t_data *data);
int		non_valid(char **map);
int		check_filename(char *filename);
int		initiate(t_data *data);

#endif