/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:37 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 10:33:53 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double	nor_angle(double angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/*
0: West wall
1: East wall
2: South wall
3: North wall
*/
int	which_wall(t_game *game, double ray_angle, int side)
{
	ray_angle = nor_angle(ray_angle);
	if (side == 0)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (0);
		else
			return (1);
	}
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = game->mlx->addr
			+ (y * game->mlx->line_length
				+ x * (game->mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	verLine(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

void	draw_buffer(t_game *game)
{
	int	x;
	int	y;

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

void	hook_init_loop(t_game *game, int x)
{
	game->hit = 0;
	game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray_dir_x = game->player->dir_x
		+ game->player->plan_x * game->camera_x;
	game->ray_dir_y = game->player->dir_y
		+ game->player->plan_y * game->camera_x;
	game->map_player_x = (int)(game->player->plyr_x);
	game->map_player_y = (int)(game->player->plyr_y);
	game->deltaDistX = (game->ray_dir_x == 0) ? 1e30 : fabs(1 / game->ray_dir_x);
	game->deltaDistY = (game->ray_dir_y == 0) ? 1e30 : fabs(1 / game->ray_dir_y);
}

void	hook_init_side_dist(t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->stepX = -1;
		game->sideDistX = (game->player->plyr_x
				- (double)game->map_player_x) * game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = ((double)game->map_player_x + 1.0
				- game->player->plyr_x) * game->deltaDistX;
	}
	if (game->ray_dir_y < 0)
	{
		game->stepY = -1;
		game->sideDistY = (game->player->plyr_y
				- game->map_player_y) * game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->map_player_y + 1.0
				- game->player->plyr_y) * game->deltaDistY;
	}
}

void	hook_find_hit(t_game *game)
{
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
		if (char_to_int(game->map->map2d
				[game->map_player_x][game->map_player_y]) > 0)
		{
			game->hit = 1;
		}
	}
}

void	hook_target_draw(t_game *game)
{
	if (game->side == 0)
		game->perpWallDist = (game->sideDistX - game->deltaDistX);
	else
		game->perpWallDist = (game->sideDistY - game->deltaDistY);
	game->pitch = 100;
	game->lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
	game->drawStart = -game->lineHeight / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->drawStart < 0)
		game->drawStart = 0;
	game->drawEnd = game->lineHeight / 2 + SCREEN_HEIGHT / 2 + game->pitch;
	if (game->drawEnd >= SCREEN_HEIGHT)
		game->drawEnd = SCREEN_HEIGHT - 1;
}
//texNum = char_to_int(game->map->map2d
//[game->map_player_x][game->map_player_y]) - 1; 
void	hook_find_text_x_y(t_game *game)
{
	game->texNum = which_wall(game, game->ray_dir_x, game->side);
	if (game->side == 0)
		game->wallX = game->player->plyr_y
			+ game->perpWallDist * game->ray_dir_y;
	else
		game->wallX = game->player->plyr_x
			+ game->perpWallDist * game->ray_dir_x;
	game->wallX -= floor((game->wallX));
	game->texX = (int)(game->wallX * (double)(TILE_SIZE));
	if (game->side == 0 && game->ray_dir_x > 0)
		game->texX = TILE_SIZE - game->texX - 1;
	if (game->side == 1 && game->ray_dir_y < 0)
		game->texX = TILE_SIZE - game->texX - 1;
	game->step = 1.0 * TILE_SIZE / game->lineHeight;
	game->texPos = (game->drawStart - game->pitch - SCREEN_HEIGHT
			/ 2 + game->lineHeight / 2) * game->step;
}

void	hook_draw_sprite(t_game *game, int x)
{
	int	y;
	int	color;
	int	texY;

	y = game->drawStart - 1;
	while (++y < game->drawEnd)
	{
		texY = (int)game->texPos & (TILE_SIZE - 1);
		game->texPos += game->step;
		color = game->sprite[(game->texNum)]->pixel_colors
		[TILE_SIZE * texY + game->texX];
		game->buffer[y][x] = color;
	}
	y = -1;
	while (++y < game->drawStart)
		game->buffer[y][x] = game->color_floor;
	y = game->drawEnd - 1;
	while (++y < SCREEN_HEIGHT)
		game->buffer[y][x] = game->color_ceilling;
}

void	hook(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		hook_init_loop(game, x);
		hook_init_side_dist(game);
		hook_find_hit(game);
		hook_target_draw(game);
		hook_find_text_x_y(game);
		hook_draw_sprite(game, x);
		x++;
	}
}

int	game_loop(void)
{
	t_game	*game;

	game = game_instance();
	mlx_destroy_image(game->mlx->mlx_p, game->mlx->img);
	game->mlx->img = mlx_new_image(game->mlx->mlx_p,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mlx->addr = mlx_get_data_addr(game->mlx->img,
			&game->mlx->bits_per_pixel, &game->mlx->line_length,
			&game->mlx->endian);
	hook(game);
	draw_buffer(game);
	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
		game->mlx->img, 0, 0);
	return (0);
}