#include "cub3d.h"
#include "libft/libft.h"

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
		return (1);
	}
	printf("debug");
	validate_struct_var(&parse, &player);
	free_parse(&parse);
	return (0);
}
