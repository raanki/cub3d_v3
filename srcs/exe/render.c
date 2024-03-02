/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 21:45:12 by ranki            ###   ########.fr       */
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

void draw_buffer(t_game *game)
{

    int x, y;

    // y = 0;
    // while (y < SCREEN_HEIGHT)
    // {
    //     x = 0;
    //     while (x < SCREEN_WIDTH)
    //     {
    //         my_mlx_pixel_put(game, x, y, game->buffer[y][x]);
    //         x++;
    //     }
    //     y++;
    // }

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
		int pitch = 100;
	  
	  	int lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
		
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;

		if(drawStart < 0)
			drawStart = 0;
			
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;


		//texturing calculations
		int texNum = char_to_int(game->map->map2d[game->map_player_x][game->map_player_y]) - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(game->side == 0)
			wallX = game->player->plyr_y + game->perpWallDist * game->ray_dir_y;
		else
			wallX = game->player->plyr_x + game->perpWallDist * game->ray_dir_x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TILE_SIZE));
		
		if(game->side == 0 && game->ray_dir_x > 0)
			texX = TILE_SIZE - texX - 1;
		if(game->side == 1 && game->ray_dir_y < 0)
			texX = TILE_SIZE - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TILE_SIZE / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (TILE_SIZE - 1);
			texPos += step;
			//printf("text %d sizetext %d\n\n",(texNum), TILE_SIZE * texY + texX);
			int color = game->sprite[(texNum)]->pixel_colors[TILE_SIZE * texY + texX];
			game->buffer[y][x] = color;
		}
		for(int y = 0; y < drawStart; y++)
		{
			game->buffer[y][x] = COLOR_FLOOR;
		}
		for(int y = drawEnd; y < SCREEN_HEIGHT; y++)
		{
			game->buffer[y][x] = COLOR_CEILLING;
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