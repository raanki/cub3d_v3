/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 22:28:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double nor_angle(double angle) // normalize the angle
{
 if (angle < 0)
  angle += (2 * M_PI);
 if (angle > (2 * M_PI))
  angle -= (2 * M_PI);
 return (angle);
}

int which_wall(t_game *game, double ray_angle, int side)
{
    ray_angle = nor_angle(ray_angle); // Normalize the angle

    if (side == 0)
    {
        if (ray_angle > 0 && ray_angle < M_PI)
            return 2; // South wall
        else
            return 3; // North wall
    }
    else
    {
        if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
            return 0; // West wall
        else
            return 1; // East wall
    }
}

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

    y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
}

void draw_buffer(t_game *game)
{

    int x, y;

	x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            my_mlx_pixel_put(game, x, y, game->buffer[y][x]);
            y++;
        }
        x++;
    }
}



void	hook(t_game *game, double move_x, double move_y)
{
	int x = 0;

	while(x < SCREEN_WIDTH)
	{
		game->hit = 0;
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->ray_dir_x = game->player->dir_x + game->player->plan_x * game->camera_x;
		game->ray_dir_y = game->player->dir_y + game->player->plan_y* game->camera_x;
		game->map_player_x = (int)(game->player->plyr_x);
		game->map_player_y = (int)(game->player->plyr_y);
		game->deltaDistX = (game->ray_dir_x == 0) ? 1e30 : fabs(1 / game->ray_dir_x);
		game->deltaDistY = (game->ray_dir_y == 0) ? 1e30 : fabs(1 / game->ray_dir_y);
		
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
				game->hit = 1; 
			} 
		}

		if(game->side == 0)
			game->perpWallDist = (game->sideDistX - game->deltaDistX); 
      	else
			game->perpWallDist = (game->sideDistY - game->deltaDistY);

		int pitch = 100;
	  
	  	int lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
		
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;

		if(drawStart < 0)
			drawStart = 0;
			
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;


		// int texNum = char_to_int(game->map->map2d[game->map_player_x][game->map_player_y]) - 1; //1 subtracted from it so that texture 0 can be used!
		
		int texNum = which_wall(game, game->ray_dir_x, game->side);

		double wallX; //where exactly the wall was hit
		if(game->side == 0)
			wallX = game->player->plyr_y + game->perpWallDist * game->ray_dir_y;
		else
			wallX = game->player->plyr_x + game->perpWallDist * game->ray_dir_x;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)(TILE_SIZE));
		
		if(game->side == 0 && game->ray_dir_x > 0)
			texX = TILE_SIZE - texX - 1;
		if(game->side == 1 && game->ray_dir_y < 0)
			texX = TILE_SIZE - texX - 1;

		double step = 1.0 * TILE_SIZE / lineHeight;
		double texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TILE_SIZE - 1);
			texPos += step;
			int color = game->sprite[(texNum)]->pixel_colors[TILE_SIZE * texY + texX];
			game->buffer[y][x] = color;
		}
		for(int y = 0; y < drawStart; y++)
		{
			game->buffer[y][x] = game->color_floor;
		}
		for(int y = drawEnd; y < SCREEN_HEIGHT; y++)
		{
			game->buffer[y][x] = game->color_ceilling;
		}
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
	for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) game->buffer[y][x] = 0;
	hook(game, 0, 0);
	draw_buffer(game);


	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
		game->mlx->img, 0, 0);
	return (0);
}