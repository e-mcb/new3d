/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 00:07:32 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/13 00:23:21 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_walkable(t_player *player, double x, double y) // a normer
{
	char **map;
	int	new_x;
	int	new_y;

	map = player->parse.map;
	new_x = x - 10;
	if (map[(int)(y)][(int)(x - 10)] == '1' || new_x < 0 || new_x > player->parse.map_width)
		return (0);
	new_x = x + 10;
	if (new_x < 0 || new_x > player->parse.map_width)
		return 0;
	if (map[(int)(y)][(int)(x + 10)] == '1')
		return (0);
	new_y = y + 10;
	if (new_y < 0 || new_y > (array_size(map) - 1))
		return 0;
	if (map[(int)(y + 10)][(int)(x)] == '1')
		return (0);
	new_y = y - 10;
	if (new_y < 0 || new_y > (array_size(map) - 1))
		return 0;
	if (map[(int)(y - 10)][(int)(x)] == '1')
		return (0);
	return (1);
}
