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

void	go_forward(t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->init_x + cos(player->init_angle) * MOVE_SPEED;
	next_y = player->init_y - sin(player->init_angle) * MOVE_SPEED;
	if (player->parse.map[(int)next_y][(int)next_x] != '1')
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
	if (player->parse.map[(int)next_y][(int)next_x] != '1')
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
	if (player->parse.map[(int)next_y][(int)next_x] != '1')
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
	if (player->parse.map[(int)next_y][(int)next_x] != '1')
	{
		player->init_x = next_x;
		player->init_y = next_y;
	}
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
