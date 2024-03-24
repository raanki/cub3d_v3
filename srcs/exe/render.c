/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 01:27:49 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_draw_buffer(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			ft_my_mlx_pixel_put(game, x, y, game->buffer[y][x]);
			y++;
		}
		x++;
	}
}


void	draw_ceilling_floor(t_game *game, int x)
{
	game->i = -1;
	while (++game->i < game->draw_start)
		game->buffer[game->i][x] = game->color_ceilling;
	game->i = game->draw_end - 1;
	while (++game->i < SCREEN_HEIGHT)
		game->buffer[game->i][x] = game->color_round;
}

void	ft_hook_draw_sprite(t_game *game, int x)
{
	int	color;
	int	tex_y;
	int	inverted_tex_x;

	if (game->draw_start < 0)
		game->draw_start = 0;
	game->i = game->draw_start;
	draw_minimap();
	draw_minimap_direction(game);
	while (game->i < game->draw_end)
	{
		tex_y = (int)game->tex_pos & (TILE_SIZE - 1);
		game->tex_pos += game->step;
		inverted_tex_x = TILE_SIZE - 1 - game->tex_x;
		if (inverted_tex_x >= 0 && inverted_tex_x < TILE_SIZE
			&& tex_y >= 0 && tex_y < TILE_SIZE)
		{
			color = game->sprite[game->tex_num]->pixel_colors[TILE_SIZE
				* tex_y + inverted_tex_x];
			game->buffer[game->i][x] = color;
		}
		game->i++;
	}
	draw_ceilling_floor(game, x);
}

void	ft_hook(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ft_hook_init_loop(game, x);
		ft_hook_init_side_dist(game);
		ft_hook_find_hit(game);
		ft_hook_target_draw(game);
		ft_hook_find_text_x_y(game);
		ft_hook_draw_sprite(game, x);
		x++;
	}
}

int	ft_game_loop(void)
{
	t_game	*game;

	game = ft_game_instance();
	mlx_destroy_image(game->mlx->mlx_p, game->mlx->img);
	game->mlx->img = mlx_new_image(game->mlx->mlx_p,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mlx->addr = mlx_get_data_addr(game->mlx->img,
			&game->mlx->bits_per_pixel, &game->mlx->line_length,
			&game->mlx->endian);
	ft_hook(game);
	ft_draw_buffer(game);
	draw_minimap();
	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
		game->mlx->img, 0, 0);
	if (game->mouse_is_press)
			mouse_moove(game->x_prev_mouse, 0,  (void *)ft_game_instance());
	return (0);
}
