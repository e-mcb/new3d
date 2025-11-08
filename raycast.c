#include "cub3d.h"

double	fix_dir(double dir)
{
	if (fabs(dir) < 1e-12)
	{
		if (dir < 0)
			return (-1e-12);
		else
			return (1e-12);
	}
	return (dir);
}

void	init_ray(t_ray *ray, t_player *player)
{
	ray->raydir_x = fix_dir(cos(player->direction_angle));
	ray->raydir_y = fix_dir(-sin(player->direction_angle));
	ray->map_x = (int)player->init_x;
	ray->map_y = (int)player->init_y;
	ray->deltadist_x = fabs(1.0 / ray->raydir_x);
	ray->deltadist_y = fabs(1.0 / ray->raydir_y);
	if (ray->raydir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->raydir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->raydir_x < 0)
		ray->sidedist_x = (player->init_x - ray->map_x) * ray->deltadist_x;
	else
		ray->sidedist_x = (ray->map_x + 1.0 - player->init_x)
			* ray->deltadist_x;
	if (ray->raydir_y < 0)
		ray->sidedist_y = (player->init_y - ray->map_y) * ray->deltadist_y;
	else
		ray->sidedist_y = (ray->map_y + 1.0 - player->init_y)
			* ray->deltadist_y;
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

double	castraydda(t_player *player)
{
	t_ray	ray;

	init_ray(&ray, player);
	perform_dda(&ray, player);
	if (ray.side == 0)
		{
			if (cos(player->direction_angle) > 0)
				player->texture_to_show = &player->textures.west;
			else
				player->texture_to_show = &player->textures.east;
			player->wall_x = player->init_y + ray.dist * sin(player->direction_angle); 
		}
		else
		{
			if (sin(player->direction_angle) > 0)
				player->texture_to_show = &player->textures.north;
			else
				player->texture_to_show = &player->textures.south;
			player->wall_x = player->init_x + ray.dist * cos(player->direction_angle);
		}
	player->wall_x -= floor(player->wall_x);
	if (ray.side == 0 && cos(player->direction_angle) > 0)
        player->wall_x = 1.0 - player->wall_x;
	if (ray.side == 1 && sin(player->direction_angle) < 0)
		player->wall_x = 1.0 - player->wall_x;
	compute_distance(&ray, player);
	correct_fisheye(&ray, player);
	return (ray.perp_dist);
}
