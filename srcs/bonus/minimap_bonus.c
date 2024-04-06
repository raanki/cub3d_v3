/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 13:03:52 by ranki            ###   ########.fr       */
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

void	ft_draw_line(int x0, int y0, int x1, int y1)
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

void	ft_draw_minimap_direction(t_game *game)
{
	int	player_minimap_x;
	int	player_minimap_y;

	if (game->is_bonus == 0)
		return ;
	player_minimap_x = game->offset_x
		+ floor(game->player->plyr_x - game->min_x) * game->tile_size_minimap;
	player_minimap_y = game->offset_y
		+ floor(game->player->plyr_y - game->min_y) * game->tile_size_minimap;
	ft_draw_line(player_minimap_x + 2, player_minimap_y + 2,
		player_minimap_x + (game->player->dir_x * 50)
		+ (-game->player->dir_y * 10),
		player_minimap_y + (game->player->dir_y * 50)
		+ (game->player->dir_x * 10));
	ft_draw_line(player_minimap_x + 2,
		player_minimap_y + 2,
		player_minimap_x + (game->player->dir_x * 50)
		- (-game->player->dir_y * 10),
		player_minimap_y + (game->player->dir_y * 50)
		- (game->player->dir_x * 10));
}

void	ft_set_min_max(t_game *game)
{
	game->tile_size_minimap = TILE_SIZE_MINIMAP;
	game->offset_x = OFFSET_X;
	game->offset_y = OFFSET_Y;
	game->min_x = (int)fmax(game->player->plyr_x - game->range, 0);
	game->max_x = (int)fmin(game->player->plyr_x
			+ game->range, game->map->w_map);
	game->min_y = (int)fmax(game->player->plyr_y - game->range, 0);
	game->max_y = (int)fmin(game->player->plyr_y
			+ game->range, game->map->h_map);
	if ((game->max_x - game->min_x) < game->msm)
	{
		game->min_x = fmax(game->min_x
				- ((game->msm - (game->max_x - game->min_x)) / 2), 0);
		game->max_x = fmin(game->max_x
				+ ((game->msm - (game->max_x - game->min_x))
					/ 2), game->map->w_map);
	}
	if ((game->max_y - game->min_y) < game->msm)
	{
		game->min_y = fmax(game->min_y
				- ((game->msm - (game->max_y - game->min_y)) / 2), 0);
		game->max_y = fmin(game->max_y
				+ ((game->msm - (game->max_y - game->min_y))
					/ 2), game->map->h_map);
	}
}

void	ft_draw_minimap(void)
{
	t_game	*game;
	int		y;
	int		x;
	int		color;

	game = ft_game_instance();
	game->range = 10;
	game->msm = 20;
	ft_set_min_max(game);
	y = game->min_y - 1;
	while (++y < game->max_y)
	{
		x = game->min_x;
		while (x < game->max_x)
		{
			color = WALL_OUT_MINIMAP;
			if (x == (int)game->player->plyr_x
				&& y == (int)game->player->plyr_y)
				color = PLAYER_COLOR;
			if (game->map->map2d[y][x] == '1')
				color = EMPTY_IN_MINIMAP;
			ft_calc_pos_minimap(x - game->min_x, y - game->min_y, color);
			x++;
		}
	}
}
