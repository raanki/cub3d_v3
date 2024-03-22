/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:49:07 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 22:31:40 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate_left(int key, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == 65361)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-game->rot_speed)
			- game->player->dir_y * sin(-game->rot_speed);
		game->player->dir_y = old_dir_x * sin(-game->rot_speed)
			+ game->player->dir_y * cos(-game->rot_speed);
		old_plane_x = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(-game->rot_speed)
			- game->player->plan_y * sin(-game->rot_speed);
		game->player->plan_y = old_plane_x * sin(-game->rot_speed)
			+ game->player->plan_y * cos(-game->rot_speed);
	}
}

void	rotate_right(int key, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == 65363)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->rot_speed)
			- game->player->dir_y * sin(game->rot_speed);
		game->player->dir_y = old_dir_x * sin(game->rot_speed)
			+ game->player->dir_y * cos(game->rot_speed);
		old_plane_x = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(game->rot_speed)
			- game->player->plan_y * sin(game->rot_speed);
		game->player->plan_y = old_plane_x * sin(game->rot_speed)
			+ game->player->plan_y * cos(game->rot_speed);
	}
}

int	find_nice_pitch(void)
{
	if (SCREEN_HEIGHT <= 500)
		return (100);
	if (SCREEN_HEIGHT <= 700)
		return (50);
	if (SCREEN_HEIGHT <= 800)
		return (40);
	if (SCREEN_HEIGHT <= 900)
		return (30);
	if (SCREEN_HEIGHT <= 1000)
		return (20);
	if (SCREEN_HEIGHT <= 1100)
		return (10);
	if (SCREEN_HEIGHT <= 1200)
		return (5);
	if (SCREEN_HEIGHT <= 1300)
		return (0);
	return (0);
}

void	ft_hook_init_loop(t_game *game, int x)
{
	game->hit = 0;
	game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray_dir_x = game->player->dir_x
		+ game->player->plan_x * game->camera_x;
	game->ray_dir_y = game->player->dir_y
		+ game->player->plan_y * game->camera_x;
	game->map_player_x = (int)floor(game->player->plyr_x);
	game->map_player_y = (int)floor(game->player->plyr_y);
	if (game->ray_dir_x == 0)
		game->delta_dist_x = 1e30;
	else
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
	if (game->delta_dist_y == 0)
		game->delta_dist_y = 1e30;
	else
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

void	ft_e_str(char *s)
{
	int	size;

	size = 0;
	while (s[size] != '\0')
	{
		size++;
	}
	write(2, "Error\n", 6);
	write(2, s, size);
	write(2, "\n", 1);
}
