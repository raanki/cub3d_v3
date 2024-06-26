/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:25 by ranki             #+#    #+#             */
/*   Updated: 2024/03/25 23:10:39 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_check_const(void)
{
	if (SCREEN_HEIGHT < 200 || SCREEN_WIDTH < 400)
	{
		ft_e_str("Resolution isn't good ! H_MIN : 200 W_MIN: 400");
		exit(EXIT_FAILURE);
	}
}

t_game	*ft_game_instance(void)
{
	static t_game	*game_instance;

	if (game_instance == NULL)
	{
		ft_check_const();
		game_instance = ft_calloc(1, sizeof(t_game));
		if (!game_instance)
			exit(EXIT_FAILURE);
		game_instance->map = NULL;
		game_instance->player = NULL;
		game_instance->sprite = NULL;
		game_instance->sprite_path = NULL;
		game_instance->mlx = NULL;
		game_instance->current_line = NULL;
		game_instance->cur_tmp = NULL;
		game_instance->valid_texture[0] = 0;
		game_instance->valid_texture[1] = 0;
		game_instance->valid_texture[2] = 0;
		game_instance->valid_texture[3] = 0;
		game_instance->x_prev_mouse = 0;
		game_instance->mouse_is_press = 0;
		game_instance->count_valid_texture = 0;
		game_instance->count_valid_color = 0;
	}
	return (game_instance);
}

double	ft_nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	ft_which_wall(t_game *game, double ray_angle, int side)
{
	ray_angle = ft_nor_angle(ray_angle);
	if (side == 0)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (1);
		else
			return (0);
	}
	else
	{
		if (game->ray_dir_y > 0)
			return (2);
		else
			return (3);
	}
}

void	ft_my_mlx_pixel_put(t_game *game, int x, int y, int color)
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
