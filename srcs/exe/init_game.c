/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 18:25:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init_map(t_game *game, char *arg)
{
	t_map		*map;
	t_player	*player;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
    //parse textures and colors before
    
	game->map = fetch_map_params(map, arg);

	if (!map->map2d)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
    game->color_ceilling = COLOR_CEILLING;
	game->color_floor = COLOR_FLOOR;
	player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		ft_free_game(game);
		exit(0);
	}
	player->dir_x = -1;
	player->dir_y = 0;
	player->plyr_x = PLAYER_START_X;
	player->plyr_y = PLAYER_START_Y;
	player->plan_x = 0;
	player->plan_y = FOV;
	game->map = map;
	game->player = player;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;
}

void	ft_start_the_game(t_game *game)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit(EXIT_FAILURE);
	game->mlx = mlx;
	game->mlx->mlx_p = mlx_init();
	if (!game->mlx->mlx_p)
	{
		exit (EXIT_FAILURE);
	}
	mlx->win_p = mlx_new_window(mlx->mlx_p, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	ft_load_sprite(game);
	mlx_loop_hook(mlx->mlx_p, &ft_game_loop, game);
	mlx_hook(game->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, game);
	mlx_hook(mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, game);
	mlx_hook(mlx->win_p, 33, 1L << 17, ft_exit, game);
	mlx_loop(mlx->mlx_p);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
