/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:07:23 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 20:56:00 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	load_sprite(t_game *game)
{
	int		width;
	int		height;
	char	*sprite_paths[4];
	int		i;
    int     y;
    int     x;
    int pixel;
    
	i = 0;
    y = 0;
	sprite_paths[0] = SPRITE_WEST;
	sprite_paths[1] = SPRITE_EAST;
	sprite_paths[2] = SPRITE_NORTH;
	sprite_paths[3] = SPRITE_SOUTH;
    game->sprite = malloc(sizeof(t_sprite *) * 4);
    if (!game->sprite){
        exit(0);
    }
	while (i < 4)
	{
		game->sprite[i] = calloc(1, sizeof(t_sprite));
		if (!game->sprite)
			exit(EXIT_FAILURE);
		game->sprite[i]->img = mlx_xpm_file_to_image(game->mlx->mlx_p, sprite_paths[i], &width, &height);
		if (!game->sprite[i]->img)
		{
			printf("Erreur lors du chargement du sprite : %s\n", sprite_paths[i]);
			free_game(game);
			exit(EXIT_FAILURE);
		}
        if (width != TILE_SIZE || height != TILE_SIZE) {
            printf("Erreur lors du chargement du sprite (bad size) : %s\n", sprite_paths[i]);
			free_game(game);
            exit(EXIT_FAILURE);
        }
		game->sprite[i]->addr = mlx_get_data_addr(game->sprite[i]->img, &game->sprite[i]->bits_per_pixel,
				&game->sprite[i]->line_length, &game->sprite[i]->endian);
		game->sprite[i]->width = width;
		game->sprite[i]->height = height;
		game->sprite[i]->pixel_colors = malloc(sizeof(int) * (TILE_SIZE * TILE_SIZE + 1));
        if(!game->sprite[i]->pixel_colors) {
            exit(0);
        }

        y = 0;
        while (y < TILE_SIZE)
        {
            x = 0;
            while (x < TILE_SIZE)
            {
                pixel = *(int*)(game->sprite[i]->addr + (y * game->sprite[i]->line_length + x * (game->sprite[i]->bits_per_pixel / 8)));
                game->sprite[i]->pixel_colors[y * TILE_SIZE + x] = pixel;
                x++;
            }
            y++;
        }
        
		i++;
	}
}

void draw_sprite_column(t_game *game, int screen_x, int start, int end, int sprite_x, int which)
{
    int color;
    double sprite_scale_factor = (double)game->sprite[which]->height / (end - start);

    for (int screen_y = start; screen_y < end; screen_y++)
    {
        int tex_y = (int)((screen_y - start) * sprite_scale_factor);
        color = *(int *)(game->sprite[which]->addr + (tex_y * game->sprite[which]->line_length + sprite_x * (game->sprite[which]->bits_per_pixel / 8)));
        my_mlx_pixel_put(game, screen_x, screen_y, color);
    }
}