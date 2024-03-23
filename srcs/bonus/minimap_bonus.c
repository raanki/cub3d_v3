/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 00:39:52 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void draw_minimap(void)
{
	t_game *game;

	game = ft_game_instance();
	game->tile_size_minimap = TILE_SIZE_MINIMAP;
	game->offset_x = OFFSET_X;
	game->offset_y = OFFSET_Y;


	for (int y = 0; y < game->map->h_map; y++)
	{
		for (int x = 0; x < game->map->w_map; x++)
		{
			int color = game->map->map2d[y][x] == '1' ? EMPTY_IN_MINIMAP : WALL_OUT_MINIMAP;
			for (int dy = 0; dy < game->tile_size_minimap; dy++)
			{
				for (int dx = 0; dx < game->tile_size_minimap; dx++)
				{
					game->buffer[game->offset_y + y * game->tile_size_minimap + dy][game->offset_x + x * game->tile_size_minimap + dx] = color;
				}
			}
		}
	}

	for (int dy = 0; dy < game->tile_size_minimap; dy++)
	{
		for (int dx = 0; dx < game->tile_size_minimap; dx++)
		{
			game->buffer[(int)(game->offset_y + floor(game->player->plyr_y) * game->tile_size_minimap + dy)][(int)(game->offset_x + floor(game->player->plyr_x) * game->tile_size_minimap + dx)] = PLAYER_COLOR;
		}
	}
}
