/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 18:36:59 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int char_to_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else
    {
        return -1;
    }
}


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
    map->map2d[16] = strdup("10044444000000000000000001");
    map->map2d[17] = strdup("10404000000000000000000001");
    map->map2d[18] = strdup("10400005000000000000000001");
    map->map2d[19] = strdup("10404000000000000000000001");
    map->map2d[20] = strdup("10044444000000000000000001");
    map->map2d[21] = strdup("1000000000000000000000001");
    map->map2d[22] = strdup("10044444000000000000000001");
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

t_game	*game_instance(void)
{
	static t_game	*game_instance;

	if (game_instance == NULL)
	{
		game_instance = calloc(1, sizeof(t_game));
		if (!game_instance)
			exit(0);
		game_instance->map = NULL;
		game_instance->player = NULL;
	}
	return (game_instance);
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

int	ft_reles(int key, t_game *game)
{

}


int	ft_exit(void *param)
{

	exit(0);
}

void	free_game(t_game *game)
{

}

int	ft_mlx_key(int key, void *gam)
{
	t_game * game = (t_game *)gam;
	double moveSpeed = 1.0;
	double rotSpeed = 0.1;
	//move forward if no wall in front of you
	if (key == XK_w || key == 122)
    {
		int x = (int)(game->player->plyr_x + game->player->dir_x * moveSpeed);
		int y = (int)(game->player->plyr_y);
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
    if (key == XK_d || key == 65363)
    {
      //both camera direction and camera plane must be rotated
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
      //both camera direction and camera plane must be rotated
      double oldDirX = game->player->dir_x;
      game->player->dir_x = game->player->dir_x * cos(rotSpeed) - game->player->dir_y * sin(rotSpeed);
      game->player->dir_y = oldDirX * sin(rotSpeed) + game->player->dir_y * cos(rotSpeed);
      double oldPlaneX = game->player->plan_x;
      game->player->plan_x = game->player->plan_x * cos(rotSpeed) - game->player->plan_y * sin(rotSpeed);
      game->player->plan_y = oldPlaneX * sin(rotSpeed) + game->player->plan_y * cos(rotSpeed);
    }
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
	mlx_loop_hook(mlx->mlx_p, &game_loop, game);
	mlx_hook(game->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, game);
	mlx_hook(mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, game);
	mlx_hook(mlx->win_p, 33, 1L << 17, ft_exit, game);
	mlx_loop(mlx->mlx_p);
	
}



int main(int argc, char **argv) {
    
	t_game	*game;
	
	game = game_instance();
	init_map(game);
	start_the_game(game);
    return 0;
}