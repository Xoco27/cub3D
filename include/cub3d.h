/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:37 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/27 17:29:01 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# ifndef SPEED
#  define SPEED 0.05
# endif
# ifndef TILE
#  define TILE 128
# endif
# ifndef PI
#  define PI 3.141592653589793
# endif
# define ERR_MAP_MISSING "Missing map"
# define ERR_WALL_INVALID "Invalid Walls"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_MALLOC "Error malloc"
# define ERR_ELEMENT "Error element"

# include <stdlib.h>
# include <math.h>
# include <errno.h>
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

typedef struct s_mapinfo
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	void	*floor;
	void	*wall;
	int		map_x;
	int		map_y;
	int		width;
	int		height;
	int		index_end_of_map;
}		t_mapinfo;

typedef struct s_player
{
	void	*down;
	double	width;
	double	height;
	double	pos_x;
	double	pos_y;
	double	vector_x;
	double	vector_y;
	double	rotation_angle;
}		t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mapinfo	mapinfo;
	char		**map;
	char		**copy;
	int			win_width;
	int			win_height;
	int			score;
	int			total;
	int			move;
	int			r;
	char		**clone;
	t_mapinfo	img;
	t_player	player;
}			t_data;

void	create_images(t_data *data);
char	*get_next_line(int fd);
void	free_map(char **map);
char	**make_tab(char *filepath, int *line_count);
char	**fill_rows(char **map, char *filepath);
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
int		check_filename(char *arg, bool cub);
int		initiate(t_data *data);
void	print_player(void *img, double x, double y, t_data *data);
void	ray(t_data *data);
int		error_message(char *detail, char *str);
int		parse_args(t_data *data, char **av);
void 	parse_map(t_data *data, char *av);
void	free_tab(void **tab);
void	fill_tab(int row, int column, int i, t_data *data);
bool	validate_walls(char **map);
int		validate_player_position(char **file);
int		validate_elements(char **file);

#endif