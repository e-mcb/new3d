/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:14:44 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 01:13:06 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define EAST 0
# define NORTH 1.57079632679
# define WEST 3.14159265359
# define SOUTH 4.71238898038
# define FOV 1.57079632679

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

typedef struct s_parse
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;		//all 4 of these are malloc'd, remember to free
	char	*texture_east;

	int		texture_fd_array[4];
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_height; // pas besoin
	int		map_width; // pas besoin
}	t_parse;

typedef struct s_player
{
	float	current_x;
	float	current_y;
	float	init_x;
	float	init_y;
	float	init_angle;
	float	direction_angle;
	float	fov;
	bool	collision;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	angular_speed;
	int		init_int_x;
	int		init_int_y;
}	t_player;

typedef struct s_list_str
{
	char			*content;
	struct s_list_str	*next;
}	t_list_str;

//lists
t_list_str	*ft_lstlast_str(t_list_str *lst);
void		ft_lstadd_back_str(t_list_str **lst, t_list_str *new_node);
t_list_str	*ft_lstnew_str(char *content);
int	ft_lstsize_str(t_list_str *lst);

//init
void	init_parse(t_parse *parse);
void	init_player(t_player *player);

//maths
float	deg_to_rad(float degrees);
float	rad_to_deg(float rad);

//parsing
int		is_texture_or_color(char *line);
int		read_map(char *filename, t_parse *parse);
int		parse_texture_or_color(char *line, t_parse *parse);
int		pad_map_lines(t_parse *parse);
int		convert_map_list_to_array(t_list *map_lines, t_parse *parse);
int		spawn_point(char **map, t_player *player);
int		validate_struct_var(t_parse *parse, t_player *player);
int		spawn_point(char **map, t_player *player);

//utils
void	ft_free_str_array(char **arr);
int		array_size(char **arr);
char	**duplicate_map(char **map, int height);
void	free_parse(t_parse *parse);
char	is_cardinal(char c);
int		is_sep(char c, const char *seps);
char	**ft_new_split(char const *s, const char *seps);
bool	is_whitespace(char c);
bool	is_valid_identifier(const char *ptr);
int		is_only_digits(char *str);

#endif
