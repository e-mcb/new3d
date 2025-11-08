/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:32:30 by mzutter           #+#    #+#             */
/*   Updated: 2025/11/08 21:07:46 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int *rgb)
{
	int	color;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	*(int *)(img->addr + y * img->line_length
			+ x * (img->bits_per_pixel / 8)) = color;
}

static void	put_pixel_wall(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	*(int *)(img->addr + y * img->line_length
			+ x * (img->bits_per_pixel / 8)) = color;
}

static void	draw_wall_texture(t_player *player, int x, t_texture_data *t)
{
	t->tex_y = (int)t->tex_pos;
	if (t->tex_y >= player->texture_to_show->height)
		t->tex_y = player->texture_to_show->height - 1;
	if (t->tex_y < 0)
		t->tex_y = 0;
	t->color = player->texture_to_show->data[t->tex_y
		* player->texture_to_show->width + t->tex_x];
	put_pixel_wall(&player->img, x, t->y++, t->color);
	t->tex_pos += t->step;
}

static void	draw_wall(t_player *player, int x, int wall_height)
{
	t_texture_data	t;

	t.start = (SCREEN_H / 2) - (wall_height / 2);
	t.end = t.start + wall_height;
	if (t.start < 0)
		t.start = 0;
	if (t.end >= SCREEN_H)
		t.end = SCREEN_H - 1;
	t.step = 1.0 * player->texture_to_show->height / wall_height;
	t.y = 0;
	while (t.y < t.start)
		put_pixel(&player->img, x, t.y++, player->parse.ceiling_color);
	t.tex_pos = (t.start - SCREEN_H / 2 + wall_height / 2) * t.step;
	if (t.tex_pos < 0)
		t.tex_pos = 0;
	t.tex_x = (int)(player->wall_x * player->texture_to_show->width);
	if (t.tex_x >= player->texture_to_show->width)
		t.tex_x = player->texture_to_show->width - 1;
	if (t.tex_x < 0)
		t.tex_x = 0;
	while (t.y <= t.end)
		draw_wall_texture(player, x, &t);
	while (t.y < SCREEN_H)
		put_pixel(&player->img, x, t.y++, player->parse.floor_color);
}

int	render_frame(t_player *player)
{
	int	x;

	rotate(player);
	if (player->key_w)
		go_forward(player);
	if (player->key_s)
		go_backward(player);
	if (player->key_a)
		go_left(player);
	if (player->key_d)
		go_right(player);
	player->direction_angle = player->init_angle + FOV / 2.0;
	x = 0;
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
