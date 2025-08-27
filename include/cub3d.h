/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:37 by cfleuret          #+#    #+#             */
/*   Updated: 2025/08/27 18:55:11 by cfleuret         ###   ########.fr       */
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

# include <stdlib.h>
# include <math.h>
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
	int		map_x;
	int		map_y;
	int		width;
	int		height;
}		t_map;

typedef struct s_player
{
	void	*down;
	int		width;
	int		height;
	double	pos_x;
	double	pos_y;
	double	angle;
}		t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**copy;
	int			win_width;
	int			win_height;
	int			move;
	double		fov;
	double		num_rays;
	double		delta_angle;
	double		max_depth;
	double		depth_vert;
	double		depth_hori;
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
void	print_player(void *img, double x, double y, t_data *data);
void	ray_cast(t_data *data, int i);
void	rotate(t_data *data, int keysym);
void	update_pos(t_data *data, double next_x, double next_y, int keysym);

#endif