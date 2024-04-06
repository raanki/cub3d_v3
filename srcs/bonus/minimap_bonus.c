/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:41 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 12:04:47 by ranki            ###   ########.fr       */
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


void	ft_draw_minimap(void)
{
	t_game	*game;
	int		y;
	int		x;
	int		color;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	int		range = 10; // La portée autour du joueur à dessiner
	int     minimap_size_min = 20; // Taille minimale pour la minimap (par exemple, 20x20)

	game = ft_game_instance();
	game->tile_size_minimap = TILE_SIZE_MINIMAP;
	game->offset_x = OFFSET_X;
	game->offset_y = OFFSET_Y;

	min_x = (int)fmax(game->player->plyr_x - range, 0);
	max_x = (int)fmin(game->player->plyr_x + range, game->map->w_map);
	min_y = (int)fmax(game->player->plyr_y - range, 0);
	max_y = (int)fmin(game->player->plyr_y + range, game->map->h_map);

    // Ajustez min_x et min_y si la taille calculée est inférieure à la taille minimale de la minimap
    if ((max_x - min_x) < minimap_size_min)
    {
        min_x = fmax(min_x - ((minimap_size_min - (max_x - min_x)) / 2), 0);
        max_x = fmin(max_x + ((minimap_size_min - (max_x - min_x)) / 2), game->map->w_map);
    }
    if ((max_y - min_y) < minimap_size_min)
    {
        min_y = fmax(min_y - ((minimap_size_min - (max_y - min_y)) / 2), 0);
        max_y = fmin(max_y + ((minimap_size_min - (max_y - min_y)) / 2), game->map->h_map);
    }
	
	y = min_y;
	while (y < max_y)
	{
		x = min_x;
		while (x < max_x)
		{
			color = (x == (int)game->player->plyr_x && y == (int)game->player->plyr_y) ? PLAYER_COLOR : WALL_OUT_MINIMAP;
			if (game->map->map2d[y][x] == '1')
				color = EMPTY_IN_MINIMAP;
				
			ft_calc_pos_minimap(x - min_x, y - min_y, color);
			x++;
		}
		y++;
	}
}


