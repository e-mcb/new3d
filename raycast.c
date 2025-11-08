#include "cub3d.h"

void	perform_dda(t_ray *ray, t_player *player)
{
	int	hit;

	hit = 0;
	ray->side = 0;
	while (!hit)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (player->parse.map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	compute_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->dist = (ray->map_x - player->init_x + (1 - ray->step_x) * 0.5)
			/ ray->raydir_x;
	else
		ray->dist = (ray->map_y - player->init_y + (1 - ray->step_y) * 0.5)
			/ ray->raydir_y;
	ray->dist = fabs(ray->dist);
}

void	define_texture(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			player->texture_to_show = &player->textures.west;
		else
			player->texture_to_show = &player->textures.east;
		player->wall_x = player->init_y + ray->dist * ray->raydir_y;
	}
	else
	{
		if (ray->raydir_y < 0)
			player->texture_to_show = &player->textures.north;
		else
			player->texture_to_show = &player->textures.south;
		player->wall_x = player->init_x + ray->dist * ray->raydir_x;
	}
}

void	correct_fisheye(t_ray *ray, t_player *player)
{
	float	delta;

	delta = player->direction_angle - player->init_angle;
	if (delta > M_PI)
		delta -= 2 * M_PI;
	if (delta < -M_PI)
		delta += 2 * M_PI;
	ray->perp_dist = ray->dist * cos(delta);
	if (ray->perp_dist < 1e-6)
		ray->perp_dist = 1e-6;
}

double	castraydda(t_player *player)
{
	t_ray	ray;

	init_ray(&ray, player);
	perform_dda(&ray, player);
	compute_distance(&ray, player);
	define_texture(&ray, player);
	player->wall_x -= floor(player->wall_x);
	if ((ray.side == 0 && ray.raydir_x > 0)
		|| (ray.side == 1 && ray.raydir_y < 0))
		player->wall_x = 1.0 - player->wall_x;
	correct_fisheye(&ray, player);
	return (ray.perp_dist);
}
