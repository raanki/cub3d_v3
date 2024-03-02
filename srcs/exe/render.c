/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 19:01:29 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    {
        char    *dst;

        dst = game->mlx->addr + (y * game->mlx->line_length + x * (game->mlx->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}


void verLine(t_game *game, int x, int start, int end, int color)
{
    int y;
	//printf("x = %d / start = %d / end = %d / color = %d\n\n", x, start, end, color);

    y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
}


void	hook(t_game *game, double move_x, double move_y)
{

	int x = 0;

	//printf("\n\n\n posx = %f / posy = %f / dirX = %f/ dirY = %f\n", game->player->plyr_x, game->player->plyr_y, game->player->dir_x, game->player->dir_y);

	while(x < SCREEN_WIDTH)
	{
		game->hit = 0;
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->ray_dir_x = game->player->dir_x + game->player->plan_x * game->camera_x;
		game->ray_dir_y = game->player->dir_y + game->player->plan_y* game->camera_x;
		//printf("\n\nray dir x = %f / ray dir y = %f\n\n", game->ray_dir_x, game->ray_dir_y );

		game->map_player_x = (int)(game->player->plyr_x);
		game->map_player_y = (int)(game->player->plyr_y);
		//printf("map player x = %d / map player y %d\n\n", map_player_x, map_player_y);
		game->deltaDistX = (game->ray_dir_x == 0) ? 1e30 : fabs(1 / game->ray_dir_x);
		game->deltaDistY = (game->ray_dir_y == 0) ? 1e30 : fabs(1 / game->ray_dir_y);
		//printf("deltaDistX = %f / map deltaDistY %f\n\n", deltaDistX, deltaDistY);

		
		if (game->ray_dir_x < 0) 
		{ 
			game->stepX = -1; 
			game->sideDistX = (game->player->plyr_x - (double)game->map_player_x) * game->deltaDistX ; 
		} 
		else
		{ 
			game->stepX = 1; 
			game->sideDistX = ((double)game->map_player_x + 1.0 - game->player->plyr_x) * game->deltaDistX ; 
		} 
		if (game->ray_dir_y < 0) 
		{ 
			game->stepY = -1 ; 
			game->sideDistY = (game->player->plyr_y - game->map_player_y) * game->deltaDistY; 
		} 
		else 
		{ 
			game->stepY = 1 ; 
			game->sideDistY = (game->map_player_y + 1.0 - game->player->plyr_y) * game->deltaDistY; 
		}

		//printf("sideDistX = %f / sideDistY %f\n\n", sideDistX, sideDistY);

	  
	  	while (game->hit == 0) 
		{
			if (game->sideDistX < game->sideDistY) 
			{ 
				game->sideDistX += game->deltaDistX; 
				game->map_player_x += game->stepX; 
				game->side = 0 ; 
			} 
			else 
			{ 
				game->sideDistY += game->deltaDistY;
				game->map_player_y += game->stepY; 
				game->side = 1 ; 
			}
			if (char_to_int(game->map->map2d[game->map_player_x][game->map_player_y]) > 0){
				//printf("hit x = %d / hit y %d\n\n", map_player_x, map_player_y);
				game->hit = 1; 
			} 
		}

		//printf("sideDistX = %f / sideDistY %f\n\n", sideDistX, sideDistY);
		//printf("side = %d\n\n", side);

		if(game->side == 0)
			game->perpWallDist = (game->sideDistX - game->deltaDistX); 
      	else
			game->perpWallDist = (game->sideDistY - game->deltaDistY);

		//printf("perpWallDist %f\n\n", perpWallDist);
	  
	  	int lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
		
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

		if(drawStart < 0)
			drawStart = 0;
			
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		int color;
		switch(char_to_int(game->map->map2d[game->map_player_x][game->map_player_y]))
		{
			case 1:  color = 0xFF0000;  break; //red
			case 2:  color = 0x00FF00;  break; //green
			case 3:  color = 0x0000FF;   break; //blue
			case 4:  color = 0x00FFFF;  break; //cyan
			default: color = 0xFFFF00; break; //yellow
		}

		// if (side == 1)
		// {
		// 	color = color / 2;
		// }

		verLine(game, x, drawStart, drawEnd, color);
		
		x++;
	}
	//printf("exit loop\n");
}

int	game_loop(void)
{
	t_game	*game;

	game = game_instance();
	mlx_destroy_image(game->mlx->mlx_p, game->mlx->img);
	game->mlx->img = mlx_new_image(game->mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mlx->addr = mlx_get_data_addr(game->mlx->img,
			&game->mlx->bits_per_pixel, &game->mlx->line_length,
			&game->mlx->endian);
	hook(game, 0, 0);


	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
		game->mlx->img, 0, 0);
	return (0);
}