/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:46:38 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/26 21:43:15 by mzutter          ###   ########.fr       */
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

static int	assign_texture(char **dst, char *src, const char *name)
{
	if (*dst)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd((char *)name, 2);
		ft_putstr_fd(" exists already\n", 2);
		return (2);
	}
	*dst = ft_strdup(src);
	if (!(*dst))
	{
		ft_putstr_fd("Error\nmalloc failed ", 2);
		ft_putstr_fd((char *)name, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	fill_texture_fields(char **splitted, t_parse **parse)
{
	if (ft_strncmp(splitted[0], "NO", 3) == 0)
		return (assign_texture(&(*parse)->texture_north, splitted[1], "North"));
	else if (ft_strncmp(splitted[0], "SO", 3) == 0)
		return (assign_texture(&(*parse)->texture_south, splitted[1], "South"));
	else if (ft_strncmp(splitted[0], "WE", 3) == 0)
		return (assign_texture(&(*parse)->texture_west, splitted[1], "West"));
	else if (ft_strncmp(splitted[0], "EA", 3) == 0)
		return (assign_texture(&(*parse)->texture_east, splitted[1], "East"));
	return (0);
}

int	fill_parse_struct(char **splitted, t_parse **parse)
{
	int	size;
	int	err;

	if (!splitted || !splitted[0])
		return (ft_putstr_fd("Error\nfill_prs_str:arr init fail\n", 2), 1);
	size = array_size(splitted);
	err = 0;
	if (size == 0 || size == 1 || size == 3 || size > 4)
	{
		ft_free_str_array(splitted);
		ft_putstr_fd("Error\nEmpty texture field\n", 2);
		return (2);
	}
	if (size == 2)
		err = fill_texture_fields(splitted, parse);
	else if ((splitted[0][0] == 'F' || splitted[0][0] == 'C') && size == 4)
		fill_color_int_array(splitted, parse);
	ft_free_str_array(splitted);
	return (err);
}
