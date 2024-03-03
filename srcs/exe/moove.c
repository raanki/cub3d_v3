/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:35 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 14:13:14 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_mlx_key(int key, void *gam)
{
	t_game	*game = (t_game *)gam;
	double	moveSpeed = 1.0;
	double	rotSpeed = 0.1;
	double	stepSide = 0.3;
	
	//move forward if no wall in front of you
	if (key == XK_w || key == 122)
	{
		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x + game->player->dir_x * moveSpeed)][(int)(game->player->plyr_y)]) == false)
			game->player->plyr_x += game->player->dir_x * moveSpeed;

		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + game->player->dir_y  * moveSpeed)]) == false)
			game->player->plyr_y += game->player->dir_y * moveSpeed;
	}
		//move backwards if no wall behind you
	if (key == XK_s || key == 115)
	{
		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x - game->player->dir_x * moveSpeed)][(int)(game->player->plyr_y)]) == false)
			game->player->plyr_x  -= game->player->dir_x  * moveSpeed;
		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y - game->player->dir_y * moveSpeed)] == false))
			game->player->plyr_y -= game->player->dir_y  * moveSpeed;
	}
		//rotate to the right
	if (key == 65363)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rotSpeed) - game->player->dir_y  * sin(-rotSpeed);
		game->player->dir_y  = oldDirX * sin(-rotSpeed) + game->player->dir_y  * cos(-rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(-rotSpeed) - game->player->plan_y * sin(-rotSpeed);
		game->player->plan_y = oldPlaneX * sin(-rotSpeed) + game->player->plan_y * cos(-rotSpeed);
	}
		//rotate to the left
	if (key == XK_a || key == 65361)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rotSpeed) - game->player->dir_y * sin(rotSpeed);
		game->player->dir_y = oldDirX * sin(rotSpeed) + game->player->dir_y * cos(rotSpeed);
		double oldPlaneX = game->player->plan_x;
		game->player->plan_x = game->player->plan_x * cos(rotSpeed) - game->player->plan_y * sin(rotSpeed);
		game->player->plan_y = oldPlaneX * sin(rotSpeed) + game->player->plan_y * cos(rotSpeed);
	}

		//move left
	if (key == XK_d || key == 100)
	{
		double	moveX = game->player->dir_y * stepSide;
    	double	moveY = -game->player->dir_x * stepSide;
			if(char_to_int(game->map->map2d[(int)(game->player->plyr_x + moveX)][(int)(game->player->plyr_y)]) == 0)
				game->player->plyr_x += moveX;
			if(char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + moveY)]) == 0)
				game->player->plyr_y += moveY;
	}

		//move right
	if (key == XK_q || key == 113)
	{
		double	moveX = -game->player->dir_y * stepSide;
    	double	moveY = game->player->dir_x * stepSide;
		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x + moveX)][(int)(game->player->plyr_y)]) == 0)
			game->player->plyr_x += moveX;
		if(char_to_int(game->map->map2d[(int)(game->player->plyr_x)][(int)(game->player->plyr_y + moveY)]) == 0)
			game->player->plyr_y += moveY;
	}
	return (0);
}
