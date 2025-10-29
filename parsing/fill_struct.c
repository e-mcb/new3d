/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:46:38 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:51:20 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_color_int_array(char **splitted, t_parse **parse)
{
	if (splitted[0][0] == 'C' && is_only_digits(splitted[1])
		&& is_only_digits(splitted[2]) && is_only_digits(splitted[3]))
	{
		(*parse)->ceiling_color[0] = ft_atoi(splitted[1]);
		(*parse)->ceiling_color[1] = ft_atoi(splitted[2]);
		(*parse)->ceiling_color[2] = ft_atoi(splitted[3]);
	}
	if (splitted[0][0] == 'F' && is_only_digits(splitted[1])
		&& is_only_digits(splitted[2]) && is_only_digits(splitted[3]))
	{
		(*parse)->floor_color[0] = ft_atoi(splitted[1]);
		(*parse)->floor_color[1] = ft_atoi(splitted[2]);
		(*parse)->floor_color[2] = ft_atoi(splitted[3]);
	}
	return ;
}

static int	fill_texture_fields(char **splitted, t_parse **parse)
{
	if (ft_strncmp(splitted[0], "NO", 3) == 0)
	{
		(*parse)->texture_north = ft_strdup(splitted[1]);
		if (!(*parse)->texture_north)
			return (ft_putstr_fd("Err:malloc failed texture_north\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "SO", 3) == 0)
	{
		(*parse)->texture_south = ft_strdup(splitted[1]);
		if (!(*parse)->texture_south)
			return (ft_putstr_fd("Err:malloc failed texture_south\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "WE", 3) == 0)
	{
		(*parse)->texture_west = ft_strdup(splitted[1]);
		if (!(*parse)->texture_west)
			return (ft_putstr_fd("Err:malloc failed texture_west\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "EA", 3) == 0)
	{
		(*parse)->texture_east = ft_strdup(splitted[1]);
		if (!(*parse)->texture_east)
			return (ft_putstr_fd("Err:malloc failed texture_east\n", 2), 1);
	}
	return (0);
}

int	fill_parse_struct(char **splitted, t_parse **parse)
{
	int	size;
	int	err;

	if (!splitted || !splitted[0])
		return (ft_putstr_fd("fill_parse_struct:failed to init arr\n", 2), 1);
	size = array_size(splitted);
	err = 0;
	if (size == 2)
		err = fill_texture_fields(splitted, parse);
	else if ((splitted[0][0] == 'F' || splitted[0][0] == 'C') && size == 4)
		fill_color_int_array(splitted, parse);
	ft_free_str_array(splitted);
	return (err);
}
