/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:35 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 18:55:27 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	moove_left(int key, t_game	*game)
{
	if (key == XK_d || key == 100)
	{
		double	moveX = game->player->dir_y * game->stepSide;
    	double	moveY = -game->player->dir_x * game->stepSide;
			if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x + moveX)][(int)(game->player->plyr_y)]) == 0)
				game->player->plyr_x += moveX;
			if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + moveY)]) == 0)
				game->player->plyr_y += moveY;
	}
}

void	moove_right(int key, t_game	*game)
{
	if (key == XK_a || key == 97)
	{
		double	moveX = -game->player->dir_y * game->stepSide;
    	double	moveY = game->player->dir_x * game->stepSide;
		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x + moveX)][(int)(game->player->plyr_y)]) == 0)
			game->player->plyr_x += moveX;
		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + moveY)]) == 0)
			game->player->plyr_y += moveY;
	}
}

void	moove_up(int key, t_game *game)
{
	if (key == XK_w || key == 122)
	{

		// printf("x = %d et y = %d\n", (int)(game->player->plyr_x + game->player->dir_x *game->moveSpeed - game->sure_mode),(int)(game->player->plyr_y) );
		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x + game->player->dir_x * game->moveSpeed - game->sure_mode)][(int)(game->player->plyr_y )]) == 0
			&& (game->player->plyr_x + game->player->dir_x * game->moveSpeed) < game->map->h_map - 1)
		{
			game->player->plyr_x += game->player->dir_x * game->moveSpeed;
			// printf("pos x est devenu : %f\n", game->player->plyr_x);
		}

		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + game->player->dir_y  * game->moveSpeed)]) == 0)
		{
			game->player->plyr_y += game->player->dir_y * game->moveSpeed;
			// printf("pos y est devenu : %f\n", game->player->plyr_x);
		}
	}
}

void	moove_back(int key, t_game *game)
{
	if (key == XK_s || key == 115)
	{
		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x - game->player->dir_x * game->moveSpeed + game->sure_mode)][(int)(game->player->plyr_y + game->sure_mode)]) == 0
		&& (game->player->plyr_x  - game->player->dir_x  * game->moveSpeed) > 1)
		{
			// printf("\ncar j'ai test : %f\n", game->player->plyr_y - game->player->dir_y * game->moveSpeed + game->sure_mode);
			game->player->plyr_x  -= game->player->dir_x  * game->moveSpeed;
			// printf("pos x est devenu : %f\n", game->player->plyr_x);
		}
		if(ft_char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y - game->player->dir_y * game->moveSpeed)] == 0)
		&& (game->player->plyr_y - game->player->dir_y * game->moveSpeed + game->sure_mode) < (game->map->h_map)
		&& (game->player->plyr_y - game->player->dir_y * game->moveSpeed) > (1))
		{
			// printf("\n2 car j'ai test : %f\n",(game->player->plyr_y - game->player->dir_y * game->moveSpeed));
			game->player->plyr_y -= game->player->dir_y  * game->moveSpeed;
			// printf("pos y est devenu : %f\n", game->player->plyr_y);
		}
	}
}

void	rotate_left(int key, t_game *game)
{
	if (key == 65361)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->rotSpeed) - game->player->dir_y * sin(game->rotSpeed);
		game->player->dir_y = oldDirX * sin(game->rotSpeed) + game->player->dir_y * cos(game->rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(game->rotSpeed) - game->player->plan_y * sin(game->rotSpeed);
		game->player->plan_y = oldPlaneX * sin(game->rotSpeed) + game->player->plan_y * cos(game->rotSpeed);
	}
}


void	rotate_right(int key, t_game *game)
{
	if (key == 65363)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-game->rotSpeed) - game->player->dir_y  * sin(-game->rotSpeed);
		game->player->dir_y  = oldDirX * sin(-game->rotSpeed) + game->player->dir_y  * cos(-game->rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(-game->rotSpeed) - game->player->plan_y * sin(-game->rotSpeed);
		game->player->plan_y = oldPlaneX * sin(-game->rotSpeed) + game->player->plan_y * cos(-game->rotSpeed);
	}
}

int	ft_mlx_key(int key, void *gam)
{
	t_game	*game;

	game = (t_game *)gam;
	game->moveSpeed = 0.2;
	game->sure_mode = 0.5;
	game->rotSpeed = 0.1;
	game->stepSide = 0.3;
	
	moove_left(key, game);
	moove_right(key, game);
	moove_up(key, game);
	moove_back(key, game);
	rotate_left(key, game);
	rotate_right(key, game);
	return (0);
}
