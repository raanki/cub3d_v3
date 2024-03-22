/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:35 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 12:49:37 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	moove_left(int key, t_game *game)
{
	double	next_x;
	double	next_y;

	if (key == XK_d || key == 100)
	{
		next_x = game->player->plyr_x - game->player->dir_y * game->moveSpeed;
		next_y = game->player->plyr_y + game->player->dir_x * game->moveSpeed;
		if (next_x < game->map->w_map && next_x > game->sure_mode)
		{
			if (game->map->map2d[(int)(next_x + game->stepSide
					* game->player->dir_x)][(int)(game->player->plyr_y)] != '1')
				game->player->plyr_x = next_x;
		}
		if (next_y < game->map->h_map - game->sure_mode_h
			&& next_y > game->sure_mode)
		{
			if (game->map->map2d[(int)(game->player->plyr_x)][(int)(next_y
					+ game->stepSide * game->player->dir_y)] != '1')
				game->player->plyr_y = next_y;
		}
	}
}

void	moove_right(int key, t_game *game)
{
	double	next_x;
	double	next_y;

	if (key == XK_a || key == 97)
	{
		next_x = game->player->plyr_x + game->player->dir_y * game->moveSpeed;
		next_y = game->player->plyr_y - game->player->dir_x * game->moveSpeed;
		if (next_x < game->map->w_map && next_x > game->sure_mode)
		{
			if (game->map->map2d[(int)(next_x + game->stepSide
					* game->player->dir_x)][(int)(game->player->plyr_y)] != '1')
				game->player->plyr_x = next_x;
		}
		if (next_y < game->map->h_map - game->sure_mode_h
			&& next_y > game->sure_mode)
		{
			if (game->map->map2d[(int)(game->player->plyr_x)][(int)(next_y
					+ game->stepSide * game->player->dir_y)] != '1')
				game->player->plyr_y = next_y;
		}
	}
}

void	moove_up(int key, t_game *game)
{
	double	next_x;
	double	next_y;

	if (key == XK_w || key == 122)
	{
		next_x = game->player->plyr_x + game->player->dir_x * game->moveSpeed;
		next_y = game->player->plyr_y + game->player->dir_y * game->moveSpeed;
		if (next_x < game->map->w_map - game->sure_mode_h
			&& next_x > game->sure_mode)
		{
			if (game->map->map2d[(int)(next_x + game->stepSide
					* game->player->dir_x)][(int)(game->player->plyr_y)] != '1')
				game->player->plyr_x = next_x;
		}
		if (next_y < game->map->h_map - game->sure_mode_h
			&& next_y > game->sure_mode)
		{
			if (game->map->map2d[(int)(game->player->plyr_x)][(int)(next_y
				+ game->stepSide * game->player->dir_y)] != '1')
				game->player->plyr_y = next_y;
		}
	}
}

void	moove_back(int key, t_game *game)
{
	double	next_x;
	double	next_y;

	if (key == XK_s || key == 115)
	{
		next_x = game->player->plyr_x - game->player->dir_x * game->moveSpeed;
		next_y = game->player->plyr_y - game->player->dir_y * game->moveSpeed;
		if (next_x < game->map->w_map && next_x > game->sure_mode)
			if (game->map->map2d[(int)(next_x + game->stepSide
					* game->player->dir_x)][(int)(game->player->plyr_y)] != '1')
				game->player->plyr_x = next_x;
		if (next_y < game->map->h_map - game->sure_mode_h
			&& next_y > game->sure_mode)
			if (game->map->map2d[(int)(game->player->plyr_x)][(int)(next_y
					+ game->stepSide * game->player->dir_y)] != '1')
				game->player->plyr_y = next_y;
	}
}

int	ft_mlx_key(int key, void *gam)
{
	t_game	*game;

	game = (t_game *)gam;
	game->moveSpeed = 0.21;
	game->sure_mode = 1.2;
	game->sure_mode_h = 0.2;
	game->rotSpeed = 0.15;
	game->stepSide = 0.31;
	moove_left(key, game);
	moove_right(key, game);
	moove_up(key, game);
	moove_back(key, game);
	rotate_left(key, game);
	rotate_right(key, game);
	return (0);
}
