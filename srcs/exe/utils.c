/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:25 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 11:46:48 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return (-1);
}

t_game	*game_instance(void)
{
	static t_game	*game_instance;

	if (game_instance == NULL)
	{
		game_instance = calloc(1, sizeof(t_game));
		if (!game_instance)
			exit(EXIT_FAILURE);
		game_instance->map = NULL;
		game_instance->player = NULL;
	}
	return (game_instance);
}

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
		if (game->ray_dir_y > 0)
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
