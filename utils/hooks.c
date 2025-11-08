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

int	key_press(int keycode, t_player	*player)
{
	if (keycode == 65307)
		close_hook(player);
	else if (keycode == 65363)
		player->key_right = 1;
	else if (keycode == 65361)
		player->key_left = 1;
	else if (keycode == 97)
		go_left(player);
	else if (keycode == 115)
		go_backward(player);
	else if (keycode == 100)
		go_right(player);
	else if (keycode == 119)
		go_forward(player);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == 65363)
		player->key_right = 0;
	else if (keycode == 65361)
		player->key_left = 0;
	return (0);
}
