/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 20:40:32 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int init_map(t_game *game) {
	t_map	*map;
	t_player *player;

	
	map = calloc(1, sizeof(t_map));

	if (!map)
		exit(0);
	game->map = map;

	map->map2d = calloc(mapWidth + 1, sizeof(char *));
	if (!map->map2d)
		exit(0);
	map->map2d[0] = strdup("1111111111111111111111111");
    map->map2d[1] = strdup("1000000000000000000000001");
    map->map2d[2] = strdup("1000000000000000000000001");
    map->map2d[3] = strdup("1000000000000000000000001");
    map->map2d[4] = strdup("10000000222220000030003001");
    map->map2d[5] = strdup("10000000200002000000000001");
    map->map2d[6] = strdup("10000000200002000030003001");
    map->map2d[7] = strdup("10000000200002000000000001");
    map->map2d[8] = strdup("10000000222220000030003001");
    map->map2d[9] = strdup("1000000000000000000000001");
    map->map2d[10] = strdup("1000000000000000000000001");
    map->map2d[11] = strdup("1000000000000000000000001");
    map->map2d[12] = strdup("1000000000000000000000001");
    map->map2d[13] = strdup("1000000000000000000000001");
    map->map2d[14] = strdup("1000000000000000000000001");
    map->map2d[15] = strdup("1000000000000000000000001");
    map->map2d[16] = strdup("10000000000000000000000001");
    map->map2d[17] = strdup("10000000000000000000000001");
    map->map2d[18] = strdup("10000000000000000000000001");
    map->map2d[19] = strdup("10000000000000000000000001");
    map->map2d[20] = strdup("10000000000000000000000001");
    map->map2d[21] = strdup("1000000000000000000000001");
    map->map2d[22] = strdup("10000000000000000000000001");
    map->map2d[23] = strdup("1111111111111111111111111");
	map->map2d[24] = NULL;
	map->w_map = mapWidth;
	map->h_map = mapHeight;
	player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		return 0;
	}
	player->dir_x = -1;
	player->dir_y = 0;
	player->plyr_x = 22;
	player->plyr_y = 12;
	player->plan_x = 0;
	player->plan_y = 0.66;
	game->map = map;
	game->player = player;
}

void	start_the_game(t_game *game)
{
	t_mlx	*mlx;

	mlx = calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit(0);
	game->mlx = mlx;
	game->mlx->mlx_p = mlx_init();
	if (!game->mlx->mlx_p) {
		exit (0);
	}
	
	mlx->win_p = mlx_new_window(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_sprite(game);
	mlx_loop_hook(mlx->mlx_p, &game_loop, game);
	mlx_hook(game->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, game);
	mlx_hook(mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, game);
	mlx_hook(mlx->win_p, 33, 1L << 17, ft_exit, game);
	mlx_loop(mlx->mlx_p);
	
}