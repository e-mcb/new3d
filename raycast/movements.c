/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:31:18 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/08 21:08:32 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	go_forward(t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->init_x + cos(player->init_angle) * MOVE_SPEED;
	next_y = player->init_y - sin(player->init_angle) * MOVE_SPEED;
	if (can_move(player, next_x, next_y))
	{
		player->init_x = next_x;
		player->init_y = next_y;
	}
}

void	go_backward(t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->init_x - cos(player->init_angle) * MOVE_SPEED;
	next_y = player->init_y + sin(player->init_angle) * MOVE_SPEED;
	if (can_move(player, next_x, next_y))
	{
		player->init_x = next_x;
		player->init_y = next_y;
	}
}

void	go_left(t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->init_x + cos(player->init_angle + M_PI / 2) * MOVE_SPEED;
	next_y = player->init_y - sin(player->init_angle + M_PI / 2) * MOVE_SPEED;
	if (can_move(player, next_x, next_y))
	{
		player->init_x = next_x;
		player->init_y = next_y;
	}
}

void	go_right(t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->init_x + cos(player->init_angle - M_PI / 2) * MOVE_SPEED;
	next_y = player->init_y - sin(player->init_angle - M_PI / 2) * MOVE_SPEED;
	if (can_move(player, next_x, next_y))
	{
		player->init_x = next_x;
		player->init_y = next_y;
	}
}

void	rotate(t_player *player)
{
	if (player->key_right)
	{
		player->init_angle -= ROTATION_SPEED;
		if (player->init_angle < 0)
			player->init_angle += 2 * M_PI;
	}
	if (player->key_left)
	{
		player->init_angle += ROTATION_SPEED;
		if (player->init_angle > 2 * M_PI)
			player->init_angle -= 2 * M_PI;
	}
}
