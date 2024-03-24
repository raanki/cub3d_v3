/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 17:27:19 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*

*/
void	set_start_angle_player(t_game *game)
{
	game->player->dir_y = 1;
	game->player->plan_x = -FOV;
	game->player->dir_x = 0;
	game->player->plan_y = 0;
	if (game->angle_player == 0)
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plan_x = 0;
		game->player->plan_y = FOV;
	}
	else if (game->angle_player == 3)
	{
		game->player->plan_x = FOV;
		game->player->dir_y = -1;
	}
	else if (game->angle_player == 2)
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plan_x = 0;
		game->player->plan_y = -FOV;
	}
}

void	ft_start_the_game(t_game *game)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	ft_check_null(mlx);
	game->mlx = mlx;
	game->mlx->mlx_p = mlx_init();
	ft_check_null(game->mlx->mlx_p);
	ft_check_res(game);
	mlx->win_p = mlx_new_window(mlx->mlx_p, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	ft_check_null(mlx->win_p);
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	ft_check_null(mlx->img);
	ft_load_sprite(game);
	mlx_loop_hook(mlx->mlx_p, &ft_game_loop, game);
	ft_launch_hook();
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
