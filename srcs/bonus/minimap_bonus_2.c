/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:49:16 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 12:14:56 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_calc_pos_minimap(int x, int y, int color)
{
	t_game	*game;
	int		pixel_x;
	int		pixel_y;
	int		dx;
	int		dy;	

	game = ft_game_instance();
	pixel_x = game->offset_x + x * game->tile_size_minimap;
	pixel_y = game->offset_y + y * game->tile_size_minimap;
	dy = 0;
	while (dy < game->tile_size_minimap)
	{
		dx = 0;
		while (dx < game->tile_size_minimap)
		{
			if (pixel_x + dx < SCREEN_WIDTH && pixel_y + dy < SCREEN_HEIGHT)
				game->buffer[pixel_y + dy][pixel_x + dx] = color;
			dx++;
		}
		dy++;
	}
}

void	ft_launch_hook(void)
{
	t_game	*g;

	g = ft_game_instance();
	mlx_hook(g->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, g);
	mlx_hook(g->mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, g);
	mlx_hook(g->mlx->win_p, 33, 1L << 17, ft_exit, g);
	if (g->is_bonus == 0)
		return ;
	mlx_hook(g->mlx->win_p, MotionNotify, PointerMotionMask, ft_mouse_moove, g);
	mlx_hook(g->mlx->win_p, ButtonPress, ButtonPressMask, ft_mouse_press, g);
	mlx_hook(g->mlx->win_p, ButtonRelease,
		ButtonReleaseMask, ft_mouse_release, g);
}

void	ft_condition_draw_line(t_game *game, int *y0, int *x0)
{
	if (game->e2 >= game->dy)
	{
		game->err += game->dy;
		*x0 += game->sx;
	}
	if (game->e2 <= game->dx)
	{
		game->err += game->dx;
		*y0 += game->sy;
	}
}
