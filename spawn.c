#include "cub3d.h"

char	is_cardinal(char c)
{
	if (c == 'w' || c == 'W' || c == 'e' || c == 'E'
		|| c == 's' || c == 'S' || c == 'n' || c == 'N')
    	return (1);
	else
		return (0);
}

float	initial_direction(char c)
{
	if (c == 'w' || c == 'W')
		return (WEST);
	if (c == 'n' || c == 'N')
		return (NORTH);
	if (c == 'e' || c == 'E')
		return (EAST);
	if (c == 's' || c == 'S')
		return (SOUTH);
	else 
		return (-1);
}

int	spawn_point(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0 && map[i][j] != '\n')
		{
			if (is_cardinal(map[i][j]))
			{
				player->init_angle = initial_direction(map[i][j]);
				player->init_x = (float)j + 0.5f; //puts the player in the center of the tile
				player->init_y = (float)i + 0.5f;
				player->init_int_x = j;
				player->init_int_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
