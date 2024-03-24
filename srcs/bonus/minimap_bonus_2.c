/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:49:16 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 04:13:35 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_calc_pos_minimap(int x, int y, int color)
{
	t_game	*game;

	game = ft_game_instance();
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

void	ft_launch_hook(void)
{
	t_game	*g;

	g = ft_game_instance();
	mlx_hook(g->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, g);
	mlx_hook(g->mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, g);
	mlx_hook(g->mlx->win_p, 33, 1L << 17, ft_exit, g);
	if (g->is_bonus == 0)
		return ;
	mlx_hook(g->mlx->win_p, MotionNotify, PointerMotionMask, mouse_moove, g);
	mlx_hook(g->mlx->win_p, ButtonPress, ButtonPressMask, mouse_press, g);
	mlx_hook(g->mlx->win_p, ButtonRelease, ButtonReleaseMask, mouse_release, g);
}
