/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:37 by cfleuret          #+#    #+#             */
/*   Updated: 2025/09/09 18:03:59 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# ifndef SPEED
#  define SPEED 0.2
# endif
# ifndef TILE
#  define TILE 64
# endif
# ifndef PI
#  define PI 3.141592653589793
# endif
# define ERR_MAP_MISSING "Missing map"
# define ERR_WALL_INVALID "Invalid Walls"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_MALLOC "Error malloc"
# define ERR_ELEMENT "Error element"
# define ERR_FILE "Error file"
# define ERR_TEXTURE_INVALID "Error invalid texture"
# define ERR_INVALID_MAP "Error Invalid map"
# define ERR_COLOR_INVALID "Error invalid color"
# define ERR_INVALID_FILENAME "Error invalid filename"

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

typedef struct s_color
{
	int	floor[3];
	int	ceiling[3];
	int	has_floor;
	int	has_ceiling;
}	t_color;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_color	color;
}	t_texture;

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
	int		width;
	int		height;
	double	pos_x;
	double	pos_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	next_x;
	double	next_y;
}			t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**tab;
	t_texture	texture;
	char		**copy;
	char		**assets;
	int			win_width;
	int			win_height;
	int			move;
	int			screen_dist;
	int			scale;
	double		fov;
	double		num_rays;
	double		delta_angle;
	double		max_depth;
	double		depth_vert;
	double		depth_hori;
	double		y_vert;
	double		x_hori;
	double		cos_a;
	double		sin_a;
	double		index;
	double		tex_pos;
	char		**clone;
	t_mapinfo	map;
	t_player	player;
	t_img		img[5];
	t_img		tex;
}				t_data;

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
int		check_filename(t_data *data, char *arg, bool cub);
int		initiate(t_data *data);
void	print_player(void *img, double x, double y, t_data *data);
void	ray_cast(t_data *data, int i);
void	rotate(t_data *data, int keysym);
void	update_pos(t_data *data, int keysym);
void	init_img(t_data *data, t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_floor_and_sky(t_data *data);
void	moving(t_data *data, int keysym);
int		render(t_data *data);
double	ray_hori_loop(t_data *data, double y_hori, double dy);
double	ray_vert_loop(t_data *data, double x_vert, double dx);
void	depth_wall_x(t_data *data, double *depth, double *wall_x, int flag);
int		error_message(t_data *data, char *detail, char *str);
int		parse_args(t_data *data, char **av);
void	parse_map(t_data *data, char *av);
void	free_tab(void **tab);
void	fill_tab(int row, int column, int i, t_data *data);
bool	validate_walls(char **map, int i);
int		validate_player_position(char **file, int i);
int		validate_elements(char **file);
int		verify_file_data(t_data *data, char **map);
int		fill_color_textures(t_texture *tex, char *line, int j);
int		create_map(t_data *data, char **file);
bool	is_map_line(char *line);
int		is_texture_line(char *line);
int		mouse(int x, int y, t_data *data);

#endif