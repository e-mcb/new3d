/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:41 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:55:17 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse(int argc, char **argv, t_player *player)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		return (1);
	}
	if (read_map(argv[1], &player->parse) != 0)
	{
		printf("Error\nCould not read map file\n");
		free_parse(&player->parse);
		return (1);
	}
	if (spawn_point(player->parse.map, player))
	{
		printf("spawn point error");
		free_parse(&player->parse);
		return (1);
	}
	return (0);
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

int	load_texture(t_player *player, t_texture *tex, char *path)
{
	int	bpp;
	int	size_line;
	int	endian;

	tex->img = mlx_xpm_file_to_image(player->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (free_player(player), 1);
	tex->data = (int *)mlx_get_data_addr(tex->img, &bpp, &size_line, &endian);
	if (!tex->data)
		return (free_player(player), 1);
	return (0);
}

int	load_all_textures(t_player	*player)
{
	if (load_texture(player, &player->textures.north, player->parse.texture_north))
		return (1);
	if (load_texture(player, &player->textures.south, player->parse.texture_south))
		return (1);
	if (load_texture(player, &player->textures.east, player->parse.texture_east))
		return (1);
	if (load_texture(player, &player->textures.west, player->parse.texture_west))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_player	player;

	init_player(&player);
	if (parse(argc, argv, &player))
		return (1);
	validate_struct_var(&player.parse, &player);
	player.direction_angle = player.init_angle + FOV / 2.0;
	player.screen_distance = (SCREEN_W / 2.0) / tan(FOV / 2.0);
	if (ft_mlx_init(&player))
		return (1);
	if (load_all_textures(&player))
		return (1);
	mlx_loop_hook(player.mlx, render_frame, &player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_hook(player.mlx_win, 3, 1L << 1, key_release, &player);
	mlx_hook(player.mlx_win, 17, 0, close_hook, &player);
	mlx_loop(player.mlx);
	free_player(&player);
	return (0);
}
