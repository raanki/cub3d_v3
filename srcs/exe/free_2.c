/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:00:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 16:59:22 by ranki            ###   ########.fr       */
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
			ft_free(game->mlx->mlx_p);
		}
		ft_free(game->mlx);
	}
}

void	ft_free_map(t_game *game, int *i)
{
	while (game && game->map && game->map->map2d && game->map->map2d[*i])
		ft_free(game->map->map2d[(*i)++]);
	if (game->map && game->map->map2d)
		ft_free(game->map->map2d);
	if (game->map)
	{
		ft_free(game->map);
	}
	if (game->player)
		ft_free(game->player);
}

int	check_res(t_game *game)
{
	int	x;
	int	y;

	mlx_get_screen_size((game->mlx->mlx_p), &x, &y);
	if (x < SCREEN_HEIGHT || y < SCREEN_HEIGHT)
	{
		ft_e_str("Resolution too big for screen");
		game->mlx->win_p = NULL;
		game->mlx->img = NULL;
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	return (0);
}
