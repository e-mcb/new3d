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
	player->screen_distance = 0.0f;
	player->init_int_x = -1;
	player->init_int_y = -1;
	player->key_left = 0;
	player->key_right = 0;
	player->dist = 0;
	player->wall_height = 0;
	player->wall_x = 0;
	init_parse(&player->parse);
}

int	ft_mlx_init(t_player *player)
{
	player->mlx = mlx_init();
	if (!player->mlx)
	{
		free_parse(&player->parse);
		return (1);
	}
	player->mlx_win = mlx_new_window(player->mlx, SCREEN_W, SCREEN_H, "Cub3d");
	if (!player->mlx_win)
	{
		free_parse(&player->parse);
		return (1);
	}
	player->img.img = mlx_new_image(player->mlx, SCREEN_W, SCREEN_H);
	if (!player->img.img)
	{
		mlx_destroy_window(player->mlx, player->mlx_win);
		free_parse(&player->parse);
		return (1);
	}
	player->img.addr = mlx_get_data_addr(player->img.img,
			&player->img.bits_per_pixel, &player->img.line_length,
			&player->img.endian);
	return (0);
}

double	fix_dir(double dir)
{
	if (fabs(dir) < 1e-12)
	{
		if (dir < 0)
			return (-1e-12);
		else
			return (1e-12);
	}
	return (dir);
}

void	init_ray(t_ray *ray, t_player *player)
{
	ray->raydir_x = fix_dir(cos(player->direction_angle));
	ray->raydir_y = fix_dir(-sin(player->direction_angle));
	ray->map_x = (int)player->init_x;
	ray->map_y = (int)player->init_y;
	ray->deltadist_x = fabs(1.0 / ray->raydir_x);
	ray->deltadist_y = fabs(1.0 / ray->raydir_y);
	if (ray->raydir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->raydir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->raydir_x < 0)
		ray->sidedist_x = (player->init_x - ray->map_x) * ray->deltadist_x;
	else
		ray->sidedist_x = (ray->map_x + 1.0 - player->init_x)
			* ray->deltadist_x;
	if (ray->raydir_y < 0)
		ray->sidedist_y = (player->init_y - ray->map_y) * ray->deltadist_y;
	else
		ray->sidedist_y = (ray->map_y + 1.0 - player->init_y)
			* ray->deltadist_y;
}
