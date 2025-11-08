/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:41:59 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/08 19:36:44 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
