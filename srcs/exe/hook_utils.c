/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:47:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 12:52:49 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		if (game->map_player_y >= game->map->h_map - 1
			|| game->map_player_x > game->map->w_map
			|| game->map_player_y <= 0 || game->map_player_x <= 0
			|| ft_char_to_int(game->map->map2d
				[game->map_player_x][game->map_player_y]) == 1)
		{
			game->hit = 1;
		}
	}
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
