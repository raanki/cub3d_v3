/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:07:23 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 14:14:22 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	manage_create_sprite(t_game *game, int *i, char *sprite_paths[4])
{
	int		width;
	int		height;

	game->sprite[*i] = calloc(1, sizeof(t_sprite));
	if (!game->sprite)
	{
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite[*i]->img = mlx_xpm_file_to_image(game->mlx->mlx_p,
			sprite_paths[*i], &width, &height);
	if ((!game->sprite[*i]->img) || (width != TILE_SIZE || height != TILE_SIZE))
	{
		printf("Error sprite : %s\n", sprite_paths[*i]);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite[*i]->addr = mlx_get_data_addr(game->sprite[*i]->img,
			&game->sprite[*i]->bits_per_pixel,
			&game->sprite[*i]->line_length, &game->sprite[*i]->endian);
	game->sprite[*i]->width = width;
	game->sprite[*i]->height = height;
}

void	manage_color_sprite(t_game *game, int *i)
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

void	manage_sprite(t_game *game, char *sprite_paths[4])
{
	int		i;

	i = 0;
	while (i < 4)
	{
		manage_create_sprite(game, &i, sprite_paths);
		game->sprite[i]->pixel_colors = malloc(sizeof(int)
				* (TILE_SIZE * TILE_SIZE + 1));
		if (!game->sprite[i]->pixel_colors)
		{
			free_game(game);
			exit(EXIT_FAILURE);
		}
		manage_color_sprite(game, &i);
		i++;
	}
}

void	load_sprite(t_game *game)
{
	char	*sprite_paths[4];

	sprite_paths[0] = SPRITE_WEST;
	sprite_paths[1] = SPRITE_EAST;
	sprite_paths[2] = SPRITE_NORTH;
	sprite_paths[3] = SPRITE_SOUTH;
	game->sprite = calloc(4, sizeof(t_sprite *));
	if (!game->sprite)
	{
		free_game(game);
		exit(EXIT_FAILURE);
	}
	manage_sprite(game, sprite_paths);
}
