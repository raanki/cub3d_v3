/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:20:18 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 15:00:31 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_exit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_free_game(game);
	exit(EXIT_SUCCESS);
}

void	ft_free_mlx(t_game *game)
{
	if (game->mlx)
	{
		if (game->mlx->img)
			mlx_destroy_image(game->mlx->mlx_p, game->mlx->img);
		if (game->mlx->win_p)
		{
			mlx_clear_window(game->mlx->mlx_p, game->mlx->win_p);
			mlx_destroy_window(game->mlx->mlx_p, game->mlx->win_p);
		}
		if (game->mlx->mlx_p)
		{
			mlx_destroy_display(game->mlx->mlx_p);
			free(game->mlx->mlx_p);
		}
		free(game->mlx);
	}
}

void	ft_free_map(t_game *game, int *i)
{
	while (game && game->map && game->map->map2d && game->map->map2d[*i])
		free(game->map->map2d[(*i)++]);
	if (game->map && game->map->map2d)
		free(game->map->map2d);
	if (game->map)
		free(game->map);
	if (game->player)
		free(game->player);
}

void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	ft_free_map(game, &i);
	if (game->sprite)
	{
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
			if (game->sprite[i])
				free(game->sprite[i]);
			i++;
		}
		free(game->sprite);
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
