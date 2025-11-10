/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:14:44 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/11 00:01:03 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define SCREEN_W 1920
# define SCREEN_H 1080
# define EAST 0
# define NORTH 1.57079632679
# define WEST 3.14159265359
# define SOUTH 4.71238898038
# define FOV 1.047197551
# define ROTATION_SPEED 0.1
# define MOVE_SPEED 0.1
# define COLLISION_RADIUS 0.3

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>

typedef struct texture_data //32bytes, 4bytes aligned
{
	int		y;
	int		start;
	int		end;
	float	step;
	float	tex_pos;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_texture_data;

typedef struct s_texture //32bytes, 8bytes aligned
{
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_textures //128bytes, 32bytes aligned
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;

typedef struct s_img //32bytes, 8bytes aligned
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_parse //72 bytes, 8bytes aligned
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;		//all 4 of these are malloc'd, remember to free
	char	*texture_east;

	char	**map;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_width;
}	t_parse;

typedef struct s_keys //24bytes, 4bytes aligned
{
	int	key_left;
	int	key_right;
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
}	t_keys;

typedef struct s_player
{
	float		current_x;
	float		current_y;
	float		init_x;
	float		init_y;
	float		init_angle;
	float		direction_angle;
	float		screen_distance;
	float		dist;
	float		wall_height;
	float		wall_x;
	int			init_int_x;
	int			init_int_y;
	void		*mlx;
	void		*mlx_win;
	t_keys		key;
	t_parse		parse;
	t_img		img;
	t_textures	textures;
	t_texture	*texture_to_show;
}	t_player;

typedef struct s_ray
{
	float		raydir_x;
	float		raydir_y;
	int			map_x;
	int			map_y;
	float		deltadist_x ;
	float		deltadist_y;
	float		sidedist_x;
	float		sidedist_y;
	int			step_x;
	int			step_y;
	int			side;
	float		dist;
	float		perp_dist;
	t_texture	*texture;
}	t_ray;

//init
void	init_parse(t_parse *parse);
void	init_player(t_player *player);
int		ft_mlx_init(t_player *player);
void	init_ray(t_ray *ray, t_player *player);
double	fix_dir(double dir);

//maths
float	deg_to_rad(float degrees);
float	rad_to_deg(float rad);

//parsing
int		read_map(char *filename, t_parse *parse);
int		spawn_point(char **map, t_player *player);
int		validate_struct_var(t_parse *parse, t_player *player);
int		spawn_point(char **map, t_player *player);
int		fill_parse_struct(char **splitted, t_parse **parse);

//utils
void	ft_free_str_array(char **arr);
int		array_size(char **arr);
char	**duplicate_map(char **map, int height);
void	free_parse(t_parse *parse);
void	free_player(t_player *player);
char	is_cardinal(char c);
int		is_sep(char c, const char *seps);
char	**ft_new_split(char const *s, const char *seps);
bool	is_whitespace(char c);
bool	is_valid_identifier(const char *ptr);
int		is_only_digits(char *str);
int		key_press(int keycode, t_player	*player);
int		key_release(int keycode, t_player *player);
int		close_hook(t_player	*player);
void	destroy_textures(t_player *player);
int		flood_fill(char **map, t_parse *parse, int x, int y);

//raycast
double	castraydda(t_player *player);
int		render_frame(t_player *player);

//movements
void	go_forward(t_player *player);
void	go_backward(t_player *player);
void	go_left(t_player *player);
void	go_right(t_player *player);
void	rotate(t_player *player);
int		can_move(t_player *player, double next_x, double next_y);

#endif
