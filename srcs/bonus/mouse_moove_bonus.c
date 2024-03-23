/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moove_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:02:17 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 00:07:59 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void    rotate_left_mouse(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-game->rot_speed_mouse)
		- game->player->dir_y * sin(-game->rot_speed_mouse);
	game->player->dir_y = old_dir_x * sin(-game->rot_speed_mouse)
		+ game->player->dir_y * cos(-game->rot_speed_mouse);
	old_plane_x = game->player->plan_x;
	game->player->plan_x = game->player->plan_x * cos(-game->rot_speed_mouse)
		- game->player->plan_y * sin(-game->rot_speed_mouse);
	game->player->plan_y = old_plane_x * sin(-game->rot_speed_mouse)
		+ game->player->plan_y * cos(-game->rot_speed_mouse);
}

void    rotate_rigth_mouse(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(game->rot_speed_mouse)
		- game->player->dir_y * sin(game->rot_speed_mouse);
	game->player->dir_y = old_dir_x * sin(game->rot_speed_mouse)
		+ game->player->dir_y * cos(game->rot_speed_mouse);
	old_plane_x = game->player->plan_x;
	game->player->plan_x = game->player->plan_x * cos(game->rot_speed_mouse)
		- game->player->plan_y * sin(game->rot_speed_mouse);
	game->player->plan_y = old_plane_x * sin(game->rot_speed_mouse)
		+ game->player->plan_y * cos(game->rot_speed_mouse);
}

int mouse_moove(int x, int y, void *param)
{

	t_game  *game;
	int     x_max;

	game = (t_game *)param;
	game->rot_speed_mouse = 0.0000001;
	game->move_speed = 0.21;
	game->rot_speed = 0.15;
	x_max = (SCREEN_WIDTH - SCREEN_WIDTH / 12);
	if ( ((x_max < x || (SCREEN_WIDTH / 12 > x))
			||  x % 60 == 0) && game->mouse_is_press)
	{
		if (x > x_max)
			rotate_right(65363,  game);
		else if ((SCREEN_WIDTH / 5 > x))
			rotate_left(65361,  game);
		else if (game->x_prev_mouse > x)
			rotate_left(65361,  game);
		else
			rotate_right(65363,  game);

	}

	game->x_prev_mouse = x;
	
}


int mouse_press(int button, int x, int y, void *gam)
{
	t_game *game;

	game = (t_game *)gam;
	(void)x;
	(void)y;
	game->mouse_is_press = 1;
	return 0;
}

int mouse_release(int button, int x, int y, void *gam)
{
	t_game *game;

	game = (t_game *)gam;
	(void)x;
	(void)y;
	game->mouse_is_press = 0;
	return 0;
}
