/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_radius.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:08:25 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/12 22:56:26 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	can_move(t_player *player, double next_x, double next_y)
// {
// 	int		map_x;
// 	int		map_y;
// 	int		i;
// 	double	offsets[4][2];

// 	i = 0;
// 	if (COLLISION_RADIUS > 1.0f)
// 		COLLISION_RADIUS = 0.1f;
// 	offsets[0][0] = COLLISION_RADIUS;
// 	offsets[0][1] = COLLISION_RADIUS;
// 	offsets[1][0] = -COLLISION_RADIUS;
// 	offsets[1][1] = COLLISION_RADIUS;
// 	offsets[2][0] = COLLISION_RADIUS;
// 	offsets[2][1] = -COLLISION_RADIUS;
// 	offsets[3][0] = -COLLISION_RADIUS;
// 	offsets[3][1] = -COLLISION_RADIUS;
// 	while (i < 4)
// 	{
// 		map_x = (int)(next_x + offsets[i][0]);
// 		map_y = (int)(next_y + offsets[i][1]);
// 		if (player->parse.map[map_y][map_x] == '1')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
