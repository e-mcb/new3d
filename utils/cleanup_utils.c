/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:36 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:52:59 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_parse(t_parse *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return ;
	free(parse->texture_north);
	free(parse->texture_south);
	free(parse->texture_west);
	free(parse->texture_east);
	if (parse->map)
	{
		i = 0;
		while (parse->map[i] != NULL)
		{
			free(parse->map[i]);
			i++;
		}
		free(parse->map);
		parse->map = NULL;
	}
}

void	free_player(t_player *player)
{
	if (!player)
		return ;
	destroy_textures(player);
	if (player->img.img && player->mlx)
	{
		mlx_destroy_image(player->mlx, player->img.img);
		player->img.img = NULL;
	}
	if (player->mlx_win && player->mlx)
	{
		mlx_destroy_window(player->mlx, player->mlx_win);
		player->mlx_win = NULL;
	}
	if (player->mlx)
	{
		mlx_destroy_display(player->mlx);
		free(player->mlx);
		player->mlx = NULL;
	}
	free_parse(&player->parse);
}

void	destroy_textures(t_player *player)
{
    if (player->textures.north.img)
        mlx_destroy_image(player->mlx, player->textures.north.img);
    if (player->textures.south.img)
        mlx_destroy_image(player->mlx, player->textures.south.img);
    if (player->textures.east.img)
        mlx_destroy_image(player->mlx, player->textures.east.img);
    if (player->textures.west.img)
        mlx_destroy_image(player->mlx, player->textures.west.img);
}
