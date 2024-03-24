/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 03:35:36 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_line(int x0, int y0, int x1, int y1)
{
	t_game	*game;
	int		e2;

	game = ft_game_instance();
	game->dx = abs(x1 - x0);
	game->sx = x0 < x1 ? 1 : -1;
	game->dy = -abs(y1 - y0);
	game->sy = y0 < y1 ? 1 : -1;
	game->err = game->dx + game->dy;
	while (1)
	{
		if (x0 >= game->offset_x && x0 < game->offset_x
			+ game->map->w_map * game->tile_size_minimap
			&& y0 >= game->offset_y && y0 < game->offset_y
			+ game->map->h_map * game->tile_size_minimap)
			game->buffer[y0][x0] = EMPTY_IN_MINIMAP;
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * game->err;
		if (e2 >= game->dy)
		{
			game->err += game->dy;
			x0 += game->sx;
		}
		if (e2 <= game->dx)
		{
			game->err += game->dx;
			y0 += game->sy;
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

void	draw_minimap(void)
{
	t_game	*game;
	int		y;
	int		x;
	int		color;

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
			color = WALL_OUT_MINIMAP;
			if (game->map->map2d[y][x] == '1')
				color = EMPTY_IN_MINIMAP;
			game->dy = 0;
			while (game->dy < game->tile_size_minimap)
			{
				game->dx = 0;
				while (game->dx < game->tile_size_minimap)
				{
					game->buffer[game->offset_y + y
						* game->tile_size_minimap + game->dy]
					[game->offset_x + x * game->tile_size_minimap
						+ game->dx] = color;
					game->dx++;
				}
				game->dy++;
			}
			x++;
		}
		y++;
	}
	game->dy = 0;
	while (game->dy < game->tile_size_minimap)
	{
		game->dx = 0;
		while (game->dx < game->tile_size_minimap)
		{
			game->buffer[(int)(game->offset_y
					+ floor(game->player->plyr_y)
					* game->tile_size_minimap + game->dy)]
			[(int)(game->offset_x + floor(game->player->plyr_x)
					* game->tile_size_minimap + game->dx)] = PLAYER_COLOR;
			game->dx++;
		}
		game->dy++;
	}
}
