#include "cub3d.h"

static void put_pixel(t_img *img, int x, int y, int *rgb) { int color; if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H) return ; color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2]; *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)) = color; }
static void put_pixel_wall(t_img *img, int x, int y, int color)
{
    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return ;
    *(int *)(img->addr + y * img->line_length
            + x * (img->bits_per_pixel / 8)) = color;
}

static void	draw_wall(t_player *player, int x, int wall_height)
{
	int	y;
	int	start;
	int	end;

	start = (SCREEN_H / 2) - (wall_height / 2);
	end = start + wall_height;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_H)
		end = SCREEN_H - 1;

	float step = 1.0 * player->texture_to_show->height / wall_height;
	float texPos = (start - SCREEN_H / 2 + wall_height / 2) * step;
	y = 0;

	while (y < start)
		put_pixel(&player->img, x, y++, player->parse.ceiling_color);

	while (y <= end)
	{
		int texY = (int)texPos;
		if (texY >= player->texture_to_show->height)
			texY = player->texture_to_show->height - 1;

		int color = player->texture_to_show->data[texY * player->texture_to_show->width + (int)player->wall_x];
		put_pixel_wall(&player->img, x, y++, color);
		
		texPos += step;
	}

	while (y < SCREEN_H)
		put_pixel(&player->img, x, y++, player->parse.floor_color);
}

// static void	draw_wall(t_player *player, int x, int wall_height)
// {
// 	int	y;
// 	int	test[3];
// 	int	start;
// 	int	end;

// 	test[0] = 11;
// 	test[1] = 22;
// 	test[2] = 12;
// 	y = 0;
// 	start = (SCREEN_H / 2) - (wall_height / 2);
// 	end = start + wall_height;
// 	if (start < 0)
// 		start = 0;
// 	if (end >= SCREEN_H)
// 		end = SCREEN_H - 1;
// 	while (y < start)
// 	{
// 		put_pixel(&player->img, x, y, player->parse.ceiling_color);
// 		y++;
// 	}
// 	while (y <= end)
// 	{
// 		put_pixel(&player->img, x, y, test);
// 		y++;
// 	}
// 	while (y <= SCREEN_H)
// 	{
// 		put_pixel(&player->img, x, y, player->parse.floor_color);
// 		y++;
// 	}
// }

static void	rotate(t_player *player)
{
	if (player->key_right)
	{
		player->init_angle -= ROTATION_SPEED;
		if (player->init_angle < 0)
			player->init_angle += 2 * M_PI;
	}
	if (player->key_left)
	{
		player->init_angle += ROTATION_SPEED;
		if (player->init_angle > 2 * M_PI)
			player->init_angle -= 2 * M_PI;
	}
}

int	render_frame(t_player *player)
{
	int	x;

	player->direction_angle = player->init_angle + FOV / 2.0;
	x = 0;
	rotate(player);
	while (x < SCREEN_W)
	{
		player->dist = castraydda(player);
		player->wall_height = (1.0 * player->screen_distance) / player->dist;
		draw_wall(player, x, (int)player->wall_height);
		player->direction_angle -= (FOV / (double)SCREEN_W);
		x++;
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win,
		player->img.img, 0, 0);
	return (0);
}
