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

int	main(int argc, char **argv)
{
	t_parse		parse;
	t_player	player;

	init_parse(&parse);
	init_player(&player);
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		return (1);
	}
	if (read_map(argv[1], &parse) != 0)
	{
		printf("Error\nCould not read map file\n");
		free_parse(&parse);
		return (1);
	}
	if (spawn_point(parse.map, &player))
	{
		printf("spawn point error");
		free_parse(&parse);
		return (1);
	}
	validate_struct_var(&parse, &player);
	free_parse(&parse);
	return (0);
}
