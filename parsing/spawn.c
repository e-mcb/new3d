/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:56 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:51:29 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	is_cardinal(char c)
{
	if (c == 'w' || c == 'W' || c == 'e' || c == 'E'
		|| c == 's' || c == 'S' || c == 'n' || c == 'N')
		return (1);
	else
		return (0);
}

float	initial_direction(char c)
{
	if (c == 'w' || c == 'W')
		return (WEST);
	if (c == 'n' || c == 'N')
		return (NORTH);
	if (c == 'e' || c == 'E')
		return (EAST);
	if (c == 's' || c == 'S')
		return (SOUTH);
	else
		return (-1);
}

int	spawn_point(char **map, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	if (!map)
		return (1);
	while (map[++i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0 && map[i][j] != '\n')
		{
			if (is_cardinal(map[i][j]))
			{
				player->init_angle = initial_direction(map[i][j]);
				player->init_x = (float)j + 0.5f;
				player->init_y = (float)i + 0.5f;
				player->init_int_x = j;
				player->init_int_y = i;
				map[i][j] = '0';
				return (0);
			}
			j++;
		}
	}
	return (1);
}
