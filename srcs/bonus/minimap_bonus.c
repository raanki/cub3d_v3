/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/03/25 19:34:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_draw_line_init(int x0, int y0, int x1, int y1)
{
	t_game	*game;

	game = ft_game_instance();
	game->dx = abs(x1 - x0);
	game->sx = -1;
	if (x0 < x1)
		game->sx = 1;
	game->dy = -abs(y1 - y0);
	game->sy = -1;
	if (y0 < y1)
		game->sy = 1;
	game->err = game->dx + game->dy;
}

void	draw_line(int x0, int y0, int x1, int y1)
{
	t_game	*game;

	game = ft_game_instance();
	ft_draw_line_init(x0, y0, x1, y1);
	while (1)
	{
		if (x0 >= game->offset_x && x0 < game->offset_x
			+ game->map->w_map * game->tile_size_minimap
			&& y0 >= game->offset_y && y0 < SCREEN_HEIGHT
			&& x0 < SCREEN_WIDTH && y0 < game->offset_y
			+ game->map->h_map * game->tile_size_minimap)
			game->buffer[y0][x0] = EMPTY_IN_MINIMAP;
		if (x0 == x1 && y0 == y1)
			break ;
		game->e2 = 2 * game->err;
		ft_condition_draw_line(game, &y0, &x0);
	}
}

void	ft_ft_draw_minimap_direction(t_game *game)
{
	int	player_minimap_x;
	int	player_minimap_y;

	if (game->is_bonus == 0)
		return ;
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

void	ft_draw_player_minimap(t_game *game)
{
	if (game->is_bonus == 0)
		return ;
	game->dy = 0;
	while (game->dy < game->tile_size_minimap)
	{
		game->dx = 0;
		while (game->dx < game->tile_size_minimap && (int)(game->offset_y
			+ floor(game->player->plyr_y)
			* game->tile_size_minimap + game->dy) < SCREEN_HEIGHT
			&& (int)(game->offset_x + floor(game->player->plyr_x)
			* game->tile_size_minimap + game->dx) > SCREEN_WIDTH)
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

void	ft_draw_minimap(void)
{
	t_game	*game;
	int		y;
	int		x;
	int		color;

	game = ft_game_instance();
	game->tile_size_minimap = TILE_SIZE_MINIMAP;
	game->offset_x = OFFSET_X;
	game->offset_y = OFFSET_Y;
	y = -1;
	while (++y < game->map->h_map)
	{
		x = 0;
		while (x < game->map->w_map)
		{
			color = WALL_OUT_MINIMAP;
			if (game->map->map2d[y][x] == '1')
				color = EMPTY_IN_MINIMAP;
			game->dy = 0;
			while (game->dy < game->tile_size_minimap)
				ft_calc_pos_minimap(x, y, color);
			x++;
		}
	}
	ft_draw_player_minimap(game);
}
