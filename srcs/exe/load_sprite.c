/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:07:23 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 12:57:05 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_sprite_memory(t_game *game, int *i, int *height, int *width)
{
	game->sprite[*i] = ft_calloc(1, sizeof(t_sprite));
	if (!game->sprite[*i])
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite[*i]->pixel_colors = NULL;
	if (game->sprite_path[*i])
	{
		game->sprite[*i]->img = mlx_xpm_file_to_image(game->mlx->mlx_p,
				game->sprite_path[*i], width, height);
	}
	else
	{
		game->sprite[*i]->img = NULL;
		game->sprite[*i]->pixel_colors = NULL;
	}
}

void	ft_manage_create_sprite(t_game *game, int *i, char *sprite_paths[4])
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	init_sprite_memory(game, i, &height, &width);
	if (!game->sprite_path[*i] || !(game->sprite[*i]->img)
		|| (width != TILE_SIZE || height != TILE_SIZE))
	{
		ft_e_str("sprite");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite[*i]->addr = mlx_get_data_addr(game->sprite[*i]->img,
			&game->sprite[*i]->bits_per_pixel,
			&game->sprite[*i]->line_length, &game->sprite[*i]->endian);
	game->sprite[*i]->width = width;
	game->sprite[*i]->height = height;
}

void	ft_manage_color_sprite(t_game *game, int *i)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = *(int *)(game->sprite[*i]->addr
					+ (y * game->sprite[*i]->line_length
						+ x * (game->sprite[*i]->bits_per_pixel / 8)));
			game->sprite[*i]->pixel_colors[y * TILE_SIZE + x] = pixel;
			x++;
		}
		y++;
	}
}

void	ft_manage_sprite(t_game *game, char *sprite_paths[4])
{
	int		i;

	i = 0;
	while (i < 4)
	{
		game->sprite[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		ft_manage_create_sprite(game, &i, game->sprite_path);
		game->sprite[i]->pixel_colors = ft_calloc((TILE_SIZE
					* TILE_SIZE + 1), sizeof(int));
		if (!game->sprite[i]->pixel_colors)
		{
			ft_free_game(game);
			exit(EXIT_FAILURE);
		}
		ft_manage_color_sprite(game, &i);
		i++;
	}
}

void	ft_load_sprite(t_game *game)
{
	game->sprite = ft_calloc(4, sizeof(t_sprite *));
	if (!game->sprite)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_manage_sprite(game, game->sprite_path);
}
