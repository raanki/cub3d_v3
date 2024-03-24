/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:49:16 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 03:49:48 by ranki            ###   ########.fr       */
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