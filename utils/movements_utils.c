/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 00:07:32 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/13 19:59:58 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_walkable(t_player *player, double x, double y)
{
	char	**map;
	int		new_x;
	int		new_y;

	map = player->parse.map;
	new_x = x - 0.3;
	if (map[(int)(y)][(int)(x - 0.3)] == '1'
		|| new_x < 0 || new_x > player->parse.map_width)
		return (0);
	new_x = x + 0.3;
	if (map[(int)(y)][(int)(x + 0.3)] == '1'
		|| new_x < 0 || new_x > player->parse.map_width)
		return (0);
	new_y = y + 0.3;
	if (map[(int)(y + 0.3)][(int)(x)] == '1'
		|| new_y < 0 || new_y > (array_size(map) - 1))
		return (0);
	new_y = y - 0.3;
	if (map[(int)(y - 0.3)][(int)(x)] == '1'
		|| new_y < 0 || new_y > (array_size(map) - 1))
		return (0);
	return (1);
}
