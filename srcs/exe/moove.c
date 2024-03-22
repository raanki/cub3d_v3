/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:35 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 11:54:05 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void moove_left(int key, t_game *game)
{
    if (key == XK_d || key == 100)
    {
		double nextX = game->player->plyr_x - game->player->dir_y * game->moveSpeed;
        double nextY = game->player->plyr_y + game->player->dir_x * game->moveSpeed;

        if (nextX < game->map->w_map && nextX > game->sure_mode)
        {
            if (game->map->map2d[(int)(nextX + game->stepSide)][(int)(game->player->plyr_y)] != '1')
                game->player->plyr_x = nextX;
        }

        if (nextY < game->map->h_map - game->sure_mode_h && nextY > game->sure_mode)
        {
            if (game->map->map2d[(int)(game->player->plyr_x)][(int)(nextY + game->stepSide)] != '1')
                game->player->plyr_y = nextY;
        }
    }
}


void moove_right(int key, t_game *game)
{
	if (key == XK_a || key == 97)
    {
       	double nextX = game->player->plyr_x + game->player->dir_y * game->moveSpeed;
        double nextY = game->player->plyr_y - game->player->dir_x * game->moveSpeed;

        if (nextX < game->map->w_map && nextX > game->sure_mode)
        {
            if (game->map->map2d[(int)(nextX + game->stepSide)][(int)(game->player->plyr_y)] != '1')
                game->player->plyr_x = nextX;
        }

        if (nextY < game->map->h_map - game->sure_mode_h && nextY > game->sure_mode)
        {
            if (game->map->map2d[(int)(game->player->plyr_x)][(int)(nextY + game->stepSide )] != '1')
                game->player->plyr_y = nextY;
        }
    }
    
}


void moove_up(int key, t_game *game)
{
	double nextX;
	double nextY;
	
    if (key == XK_w || key == 122)
    {

        double nextX = game->player->plyr_x + game->player->dir_x * game->moveSpeed;
        double nextY = game->player->plyr_y + game->player->dir_y * game->moveSpeed;

        if (nextX < game->map->w_map - game->sure_mode_h && nextX > game->sure_mode)
        {
            if (game->map->map2d[(int)(nextX + game->stepSide)][(int)(game->player->plyr_y)] != '1')
                game->player->plyr_x = nextX;
        }

        if (nextY < game->map->h_map - game->sure_mode_h && nextY > game->sure_mode)
        {
            if (game->map->map2d[(int)(game->player->plyr_x)][(int)(nextY + game->stepSide)] != '1')
                game->player->plyr_y = nextY;
        }
    }
}



void moove_back(int key, t_game *game)
{
    if (key == XK_s || key == 115)
    {
        double nextX = game->player->plyr_x - game->player->dir_x * game->moveSpeed;
        double nextY = game->player->plyr_y - game->player->dir_y * game->moveSpeed;

        if (nextX < game->map->w_map && nextX > game->sure_mode)
        {
            if (game->map->map2d[(int)(nextX + game->stepSide)][(int)(game->player->plyr_y)] != '1')
                game->player->plyr_x = nextX;
        }

        if (nextY < game->map->h_map - game->sure_mode_h && nextY > game->sure_mode)
        {
            if (game->map->map2d[(int)(game->player->plyr_x)][(int)(nextY + game->stepSide)] != '1')
                game->player->plyr_y = nextY;
        }
    }
}



void	rotate_left(int key, t_game *game)
{
	if (key == 65361)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-game->rotSpeed) - game->player->dir_y  * sin(-game->rotSpeed);
		game->player->dir_y  = oldDirX * sin(-game->rotSpeed) + game->player->dir_y  * cos(-game->rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(-game->rotSpeed) - game->player->plan_y * sin(-game->rotSpeed);
		game->player->plan_y = oldPlaneX * sin(-game->rotSpeed) + game->player->plan_y * cos(-game->rotSpeed);
	}
}


void	rotate_right(int key, t_game *game)
{
	if (key == 65363)
	{
		
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->rotSpeed) - game->player->dir_y * sin(game->rotSpeed);
		game->player->dir_y = oldDirX * sin(game->rotSpeed) + game->player->dir_y * cos(game->rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(game->rotSpeed) - game->player->plan_y * sin(game->rotSpeed);
		game->player->plan_y = oldPlaneX * sin(game->rotSpeed) + game->player->plan_y * cos(game->rotSpeed);
	}
}

int	ft_mlx_key(int key, void *gam)
{
	t_game	*game;

	game = (t_game *)gam;
	game->moveSpeed = 0.2;
	game->sure_mode = 1.2;
	game->sure_mode_h = 0.2;
	game->rotSpeed = 0.15;
	game->stepSide = 0.3;

	moove_left(key, game);
	moove_right(key, game);
	moove_up(key, game);
	moove_back(key, game);
	rotate_left(key, game);
	rotate_right(key, game);
	return (0);
}
