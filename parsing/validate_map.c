/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:59 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/08 02:33:14 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	validate_rgb_array(t_parse *parse)
{
	if (parse->ceiling_color[0] > 255 || parse->ceiling_color[0] < 0
		|| parse->ceiling_color[1] > 255 || parse->ceiling_color[1] < 0
		|| parse->ceiling_color[2] > 255 || parse->ceiling_color[2] < 0)
		return (ft_putstr_fd("Invalid ceiling rgb", 2), 1);
	if (parse->floor_color[0] > 255 || parse->floor_color[0] < 0
		|| parse->floor_color[1] > 255 || parse->floor_color[1] < 0
		|| parse->floor_color[2] > 255 || parse->floor_color[2] < 0)
		return (ft_putstr_fd("Invalid floor rgb", 2), 1);
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

void	pad_map(t_parse *parse)
{
	int		y;
	int		row_len;
	char	*new_row;

	y = 0;
	while (parse->map[y] != NULL)
	{
		row_len = ft_strlen(parse->map[y]);
		if (row_len > 0 && parse->map[y][row_len - 1] == '\n')
		{
			parse->map[y][row_len - 1] = '\0';
			row_len--;
		}
		if (row_len < parse->map_width)
		{
			new_row = malloc(parse->map_width + 1);
			if (!new_row)
				return ;
			ft_strlcpy(new_row, parse->map[y], parse->map_width + 1);
			ft_memset(new_row + row_len, '0', parse->map_width - row_len);
			new_row[parse->map_width] = '\0';
			free(parse->map[y]);
			parse->map[y] = new_row;
		}
		y++;
	}
}

// int	check_xpm_files(t_parse *parse)
// {
// 	int	error;
// 	int	fd;

// 	error = 0;
// 	fd = open(parse->texture_north, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("check_xpm_files:failed to open texture file north\n", 2);
// 		error = 1;
// 	}
// 	if (fd > 2)
// 		close (fd);
// 	fd = open(parse->texture_south, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("check_xpm_files:failed to open texture file south\n", 2);
// 		error = 1;
// 	}
// 	if (fd > 2)
// 		close (fd);
// 	fd = open(parse->texture_east, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("check_xpm_files:failed to open texture file east\n", 2);
// 		error = 1;
// 	}
// 	if (fd > 2)
// 		close (fd);
// 	fd = open(parse->texture_west, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("check_xpm_files:failed to open texture file west\n", 2);
// 		error = 1;
// 	}
// 	if (fd > 2)
// 		close (fd);
// 	return (error);
// }

static void	outer_void_to_wall(t_parse **parse, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map_copy[i] && (*parse)->map[i])
	{
		j = 0;
		while (map_copy[i][j] && (*parse)->map[i][j])
		{
			if (map_copy[i][j] == '0')
			{
				(*parse)->map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
}

int	validate_struct_var(t_parse *parse, t_player *player)
{
	char	**map_copy;
	
	if (validate_rgb_array(parse))
		return (1);
	pad_map(parse);
	map_copy = duplicate_map(parse->map, array_size(parse->map));
	if (!map_copy)
	{
		printf("map_copy malloc error\n");
		return (1);
	}
	int i = -1;
	while (parse->map[++i])
		printf("map:%s\n", parse->map[i]);
	if (!flood_fill(map_copy, parse, player->init_int_x, player->init_int_y))
	{
		ft_putstr_fd("validate_struct_var:flood_fill error", 2);
		ft_free_str_array(map_copy);
		return (1);
	}
	outer_void_to_wall(&parse, map_copy);
	ft_free_str_array(map_copy);
	// if (check_xpm_files(parse))
	// {
	// 	return (1);      //Redondant -> mlx_xpm_to_img renvoie null si open fail mais j'ai laisse la fonction
	// }
	return (0);
}