/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 02:36:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_line(int x0, int y0, int x1, int y1)
{
	t_game	*game;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	game = ft_game_instance();
	while (1)
	{
		if (x0 >= game->offset_x && x0 < game->offset_x
			+ game->map->w_map * game->tile_size_minimap
			&& y0 >= game->offset_y && y0 < game->offset_y
			+ game->map->h_map * game->tile_size_minimap)
			game->buffer[y0][x0] = EMPTY_IN_MINIMAP;
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_minimap_direction(t_game *game)
{
	int	player_minimap_x;
	int	player_minimap_y;

	player_minimap_x = game->offset_x
		+ floor(game->player->plyr_x) * game->tile_size_minimap;
	player_minimap_y = game->offset_y
		+ floor(game->player->plyr_y) * game->tile_size_minimap;
	draw_line(player_minimap_x + 2, player_minimap_y + 2,
		player_minimap_x + (game->player->dir_x * 50)
		+ (-game->player->dir_y * 10),
		player_minimap_y + (game->player->dir_y * 50)
		+ (game->player->dir_x * 10));
	draw_line(player_minimap_x + 2,
		player_minimap_y + 2,
		player_minimap_x + (game->player->dir_x * 50)
		- (-game->player->dir_y * 10),
		player_minimap_y + (game->player->dir_y * 50)
		- (game->player->dir_x * 10));
}

void draw_minimap(void)
{
    t_game *game;
    int y, x, dy, dx;
    int color;

    game = ft_game_instance();
    game->tile_size_minimap = TILE_SIZE_MINIMAP;
    game->offset_x = OFFSET_X;
    game->offset_y = OFFSET_Y;

    y = 0;
    while (y < game->map->h_map)
    {
        x = 0;
        while (x < game->map->w_map)
        {
            color = game->map->map2d[y][x] == '1' ? EMPTY_IN_MINIMAP : WALL_OUT_MINIMAP;
            dy = 0;
            while (dy < game->tile_size_minimap)
            {
                dx = 0;
                while (dx < game->tile_size_minimap)
                {
                    game->buffer[game->offset_y + y * game->tile_size_minimap + dy][game->offset_x + x * game->tile_size_minimap + dx] = color;
                    dx++;
                }
                dy++;
            }
            x++;
        }
        y++;
    }

    dy = 0;
    while (dy < game->tile_size_minimap)
    {
        dx = 0;
        while (dx < game->tile_size_minimap)
        {
            game->buffer[(int)(game->offset_y + floor(game->player->plyr_y) * game->tile_size_minimap + dy)][(int)(game->offset_x + floor(game->player->plyr_x) * game->tile_size_minimap + dx)] = PLAYER_COLOR;
            dx++;
        }
        dy++;
    }
}

