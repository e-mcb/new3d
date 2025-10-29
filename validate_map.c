#include "cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	validate_rgb_array(t_parse *parse)
{
	printf("%d, %d, %d\n", parse->ceiling_color[0], parse->ceiling_color[1], parse->ceiling_color[2]);
	if (parse->ceiling_color[0] > 255 || parse->ceiling_color[0] < 0
		|| parse->ceiling_color[1] > 255 || parse->ceiling_color[1] < 0
		|| parse->ceiling_color[2] > 255 || parse->ceiling_color[2] < 0)
		return(ft_putstr_fd("Invalid ceiling rgb", 2), 1);
	if (parse->floor_color[0] > 255 || parse->floor_color[0] < 0
		|| parse->floor_color[1] > 255 || parse->floor_color[1] < 0
		|| parse->floor_color[2] > 255 || parse->floor_color[2] < 0)
		return(ft_putstr_fd("Invalid floor rgb", 2), 1);
	return (0);
}

int	flood_fill(char **map, t_parse *parse, int x, int y)
{
	char	c;

	if (x < 0 || y < 0)
		return (0);
	c = map[y][x];
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1' || c == 'V')
		return (1);
	if (!is_valid_map_char(c))
		return (0);
	map[y][x] = 'V';
	if (!flood_fill(map, parse, x + 1, y))
		return (0);
	if (!flood_fill(map, parse, x - 1, y))
		return (0);
	if (!flood_fill(map, parse, x, y + 1))
		return (0);
	if (!flood_fill(map, parse, x, y - 1))
		return (0);
	return (1);
}

int	check_xpm_files(t_parse *parse) // redundant 
{
	int	error;
	int	fd;

	error = 0;
	fd = open(parse->texture_north, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("check_xpm_files:failed to open texture file north\n", 2);
		error = 1;
	}
	if (fd > 2)
		close (fd);
	fd = open(parse->texture_south, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("check_xpm_files:failed to open texture file south\n", 2);
		error = 1;
	}
	if (fd > 2)
		close (fd);
	fd = open(parse->texture_east, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("check_xpm_files:failed to open texture file east\n", 2);
		error = 1;
	}
	if (fd > 2)
		close (fd);
	fd = open(parse->texture_west, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("check_xpm_files:failed to open texture file west\n", 2);
		error = 1;
	}
	if (fd > 2)
		close (fd);
	return (error);
}

int	validate_struct_var(t_parse *parse, t_player *player)
{
	(void) player;
	// spawn_point(parse->map, player);
	if (validate_rgb_array(parse))
		return(1);
	if(flood_fill(parse->map, parse, player->init_int_x, player->init_int_y))
	{
		ft_putstr_fd("validate_struct_var:flood_fill error", 2);
		return (1);
	}
	if (check_xpm_files(parse))
	{
		return (1);
	}
	return (0);
}