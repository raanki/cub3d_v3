/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:20:18 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 23:05:37 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_free_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->sprite[i])
		{
			i++;
			continue ;
		}
		if (game->sprite[i]->pixel_colors)
			free(game->sprite[i]->pixel_colors);
		if (game->sprite[i]->img)
			mlx_destroy_image(game->mlx->mlx_p, game->sprite[i]->img);
		free(game->sprite[i]);
		i++;
	}
	free(game->sprite);
}

void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	ft_free_map(game, &i);
	i = 0;
	if (game->sprite)
		ft_free_sprite(game);
	if (game->sprite_path)
	{
		while (i < 4)
		{
			if (game->sprite_path[i])
				free(game->sprite_path[i]);
			i++;
		}
		free(game->sprite_path);
	}
	ft_free_mlx(game);
	free(game);
}

int	ft_reles(int key, t_game *game)
{
	if (key == 65307)
	{
		ft_free_game(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
