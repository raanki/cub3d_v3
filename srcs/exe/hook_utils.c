/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:47:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 10:00:27 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_hook_init_loop(t_game *game, int x)
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
		game->delta_dist_x = 1e30;
	else
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
	if (game->delta_dist_y == 0)
		game->delta_dist_y = 1e30;
	else
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

void	ft_hook_init_side_dist(t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (game->player->plyr_x
				- (double)game->map_player_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = ((double)game->map_player_x + 1.0
				- game->player->plyr_x) * game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->player->plyr_y
				- game->map_player_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (game->map_player_y + 1.0
				- game->player->plyr_y) * game->delta_dist_y;
	}
}

void	ft_hook_find_hit(t_game *game)
{
	while (game->hit == 0)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			game->map_player_x += game->step_x;
			game->side = 0 ;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			game->map_player_y += game->step_y;
			game->side = 1 ;
		}
		if (game->map_player_y >= game->map->h_map - 1 || game->map_player_x > game->map->w_map
			|| game->map_player_y <= 0 || game->map_player_x <= 0
			|| ft_char_to_int(game->map->map2d
				[game->map_player_x][game->map_player_y]) == 1)
		{
			game->hit = 1;
		}
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

void	ft_hook_target_draw(t_game *game)
{
	if (game->side == 0)
		game->perp_wall_dist = (game->side_dist_x - game->delta_dist_x);
	else
		game->perp_wall_dist = (game->side_dist_y - game->delta_dist_y);
	game->pitch = find_nice_pitch();
	game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->draw_end >= SCREEN_HEIGHT)
		game->draw_end = SCREEN_HEIGHT - 1;
}

//tex_num = char_to_int(game->map->map2d
//[game->map_player_x][game->map_player_y]) - 1;
void	ft_hook_find_text_x_y(t_game *game)
{
	game->tex_num = ft_which_wall(game, game->ray_dir_x, game->side);
	if (game->side == 0)
		game->wall_x = game->player->plyr_y
			+ game->perp_wall_dist * game->ray_dir_y;
	else
		game->wall_x = game->player->plyr_x
			+ game->perp_wall_dist * game->ray_dir_x;
	game->wall_x -= floor((game->wall_x));
	game->tex_x = (int)(game->wall_x * (double)(TILE_SIZE));
	if (game->side == 0 && game->ray_dir_x > 0)
		game->tex_x = TILE_SIZE - game->tex_x - 1;
	if (game->side == 1 && game->ray_dir_y < 0)
		game->tex_x = TILE_SIZE - game->tex_x - 1;
	game->step = 1.0 * TILE_SIZE / game->line_height;
	game->tex_pos = (game->draw_start - game->pitch - SCREEN_HEIGHT
			/ 2 + game->line_height / 2) * game->step;
}
