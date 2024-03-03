/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:47:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 10:52:30 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	hook_init_loop(t_game *game, int x)
{
	game->hit = 0;
	game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray_dir_x = game->player->dir_x
		+ game->player->plan_x * game->camera_x;
	game->ray_dir_y = game->player->dir_y
		+ game->player->plan_y * game->camera_x;
	game->map_player_x = (int)(game->player->plyr_x);
	game->map_player_y = (int)(game->player->plyr_y);
	if (game->ray_dir_x == 0)
		game->deltaDistX = 1e30;
	else
		game->deltaDistX = fabs(1 / game->ray_dir_x);
	if (game->deltaDistY == 0)
		game->deltaDistY = 1e30;
	else
		game->deltaDistY = fabs(1 / game->ray_dir_y);
}

void	hook_init_side_dist(t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->stepX = -1;
		game->sideDistX = (game->player->plyr_x
				- (double)game->map_player_x) * game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = ((double)game->map_player_x + 1.0
				- game->player->plyr_x) * game->deltaDistX;
	}
	if (game->ray_dir_y < 0)
	{
		game->stepY = -1;
		game->sideDistY = (game->player->plyr_y
				- game->map_player_y) * game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->map_player_y + 1.0
				- game->player->plyr_y) * game->deltaDistY;
	}
}

void	hook_find_hit(t_game *game)
{
	while (game->hit == 0)
	{
		if (game->sideDistX < game->sideDistY)
		{
			game->sideDistX += game->deltaDistX;
			game->map_player_x += game->stepX;
			game->side = 0 ;
		}
		else
		{
			game->sideDistY += game->deltaDistY;
			game->map_player_y += game->stepY;
			game->side = 1 ;
		}
		if (char_to_int(game->map->map2d
				[game->map_player_x][game->map_player_y]) > 0)
		{
			game->hit = 1;
		}
	}
}

void	hook_target_draw(t_game *game)
{
	if (game->side == 0)
		game->perpWallDist = (game->sideDistX - game->deltaDistX);
	else
		game->perpWallDist = (game->sideDistY - game->deltaDistY);
	game->pitch = 100;
	game->lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
	game->drawStart = -game->lineHeight / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->drawStart < 0)
		game->drawStart = 0;
	game->drawEnd = game->lineHeight / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->drawEnd >= SCREEN_HEIGHT)
		game->drawEnd = SCREEN_HEIGHT - 1;
}

//texNum = char_to_int(game->map->map2d
//[game->map_player_x][game->map_player_y]) - 1;
void	hook_find_text_x_y(t_game *game)
{
	game->texNum = which_wall(game, game->ray_dir_x, game->side);
	if (game->side == 0)
		game->wallX = game->player->plyr_y
			+ game->perpWallDist * game->ray_dir_y;
	else
		game->wallX = game->player->plyr_x
			+ game->perpWallDist * game->ray_dir_x;
	game->wallX -= floor((game->wallX));
	game->texX = (int)(game->wallX * (double)(TILE_SIZE));
	if (game->side == 0 && game->ray_dir_x > 0)
		game->texX = TILE_SIZE - game->texX - 1;
	if (game->side == 1 && game->ray_dir_y < 0)
		game->texX = TILE_SIZE - game->texX - 1;
	game->step = 1.0 * TILE_SIZE / game->lineHeight;
	game->texPos = (game->drawStart - game->pitch - SCREEN_HEIGHT
			/ 2 + game->lineHeight / 2) * game->step;
}
