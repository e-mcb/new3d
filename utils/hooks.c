/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:34:02 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/10 23:12:11 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_hook(t_player	*player)
{
	if (!player)
		return (0);
	if (player->mlx)
		mlx_loop_end(player->mlx);
	free_player(player);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == 65307)
		close_hook(player);
	else if (keycode == 65363)
		player->key.key_right = 1;
	else if (keycode == 65361)
		player->key.key_left = 1;
	else if (keycode == 119)
		player->key.key_w = 1;
	else if (keycode == 115)
		player->key.key_s = 1;
	else if (keycode == 97)
		player->key.key_a = 1;
	else if (keycode == 100)
		player->key.key_d = 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == 65363)
		player->key.key_right = 0;
	else if (keycode == 65361)
		player->key.key_left = 0;
	else if (keycode == 119)
		player->key.key_w = 0;
	else if (keycode == 115)
		player->key.key_s = 0;
	else if (keycode == 97)
		player->key.key_a = 0;
	else if (keycode == 100)
		player->key.key_d = 0;
	return (0);
}
