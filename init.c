/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:40 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 22:38:31 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_parse *parse)
{
	int	i;

	if (!parse)
		return ;
	parse->texture_north = NULL;
	parse->texture_south = NULL;
	parse->texture_west = NULL;
	parse->texture_east = NULL;
	i = 0;
	while (i < 3)
	{
		parse->floor_color[i] = -1;
		parse->ceiling_color[i] = -1;
		i++;
	}
	parse->map = NULL;
	parse->map_width = -1;
}

void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->current_x = 0.0f;
	player->current_y = 0.0f;
	player->init_x = -1.0f;
	player->init_y = -1.0f;
	player->init_angle = -1.0f;
	player->direction_angle = 0.0f;
	player->fov = FOV;
	player->collision = false;
	player->dir_x = 0.0f;
	player->dir_y = 0.0f;
	player->plane_x = 0.0f;
	player->plane_y = 0.0f;
	player->move_speed = 0.05f;
	player->angular_speed = 0.03f;
	player->init_int_x = -1;
	player->init_int_y = -1;
}
