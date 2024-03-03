/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 11:58:52 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	verLine(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

void	draw_buffer(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y, game->buffer[y][x]);
			y++;
		}
		x++;
	}
}

void	hook_draw_sprite(t_game *game, int x)
{
	int	y;
	int	color;
	int	texY;

	y = game->drawStart - 1;
	while (++y < game->drawEnd)
	{
		texY = (int)game->texPos & (TILE_SIZE - 1);
		game->texPos += game->step;
		color = game->sprite[(game->texNum)]->pixel_colors
		[TILE_SIZE * texY + game->texX];
		game->buffer[y][x] = color;
	}
	y = -1;
	while (++y < game->drawStart)
		game->buffer[y][x] = game->color_floor;
	y = game->drawEnd - 1;
	while (++y < SCREEN_HEIGHT)
		game->buffer[y][x] = game->color_ceilling;
}

void	hook(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		hook_init_loop(game, x);
		hook_init_side_dist(game);
		hook_find_hit(game);
		hook_target_draw(game);
		hook_find_text_x_y(game);
		hook_draw_sprite(game, x);
		x++;
	}
}

int	game_loop(void)
{
	t_game	*game;

	game = game_instance();
	mlx_destroy_image(game->mlx->mlx_p, game->mlx->img);
	game->mlx->img = mlx_new_image(game->mlx->mlx_p,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mlx->addr = mlx_get_data_addr(game->mlx->img,
			&game->mlx->bits_per_pixel, &game->mlx->line_length,
			&game->mlx->endian);
	hook(game);
	draw_buffer(game);
	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
		game->mlx->img, 0, 0);
	return (0);
}
