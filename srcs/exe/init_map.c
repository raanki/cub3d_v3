/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:01:31 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 22:05:44 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init_player_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->map->map2d = NULL;
	game->player = malloc(sizeof(t_player));
	if (game->player == NULL)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite_path = ft_calloc(5, sizeof(char *));
	if (!game->sprite_path)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->sprite_path[0] = ft_strdup("nothing but essential");
	game->sprite_path[1] = ft_strdup("nothing but essential");
	game->sprite_path[2] = ft_strdup("nothing but essential");
	game->sprite_path[3] = ft_strdup("nothing but essential");
}

void	ft_set_map_color_texture(t_game *game)
{
	while ((game->current_line != NULL && (game->count_valid_texture < 4
				|| game->count_valid_color < 2)) || game->first)
	{
		game->first = 0;
		game->current_line = get_next_line(game->fd);
		if (!game->current_line)
			break ;
		game->cur_tmp = ft_strdup(game->current_line);
		if (is_line_texture(game->current_line))
		{
			if (game->sprite_path[game->current_sprite])
				free(game->sprite_path[game->current_sprite]);
			game->sprite_path[game->current_sprite] = parse_lt(game->cur_tmp);
			game->count_valid_texture++;
			game->index_sprite_path++;
		}
		else if (is_line_color(game->current_line))
		{
			parse_line_color(game, game->cur_tmp);
			game->count_valid_color++;
		}
		free(game->cur_tmp);
		free(game->current_line);
	}
}

void	ft_check_texture_color_fetch(t_game *game, char *arg)
{
	game->sprite_path[4] = NULL;
	if (game->count_valid_texture != 4)
	{
		ft_free_game(game);
		printf("You have to put 4 valid textures\n");
		exit(EXIT_FAILURE);
	}
	if (game->count_valid_color != 2)
	{
		ft_free_game(game);
		printf("You have to put 2 valid colors\n");
		exit(EXIT_FAILURE);
	}
	game->map = fetch_map_params(game->fd, game->map, arg, game);
	if (!game->map->map2d)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
}

int	check_res(t_game *game)
{
	int	x;
	int	y;

	mlx_get_screen_size((game->mlx->mlx_p), &x, &y);
	if (x < SCREEN_HEIGHT || y < SCREEN_HEIGHT)
	{
		ft_e_str("Resolution too big for screen");
		game->mlx->win_p = NULL;
		game->mlx->img = NULL;
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	ft_init_map(t_game *game, char *arg)
{
	ft_init_player_map(game);
	game->fd = open_fd(game, arg);
	game->index_sprite_path = 0;
	game->current_sprite = 0;
	game->count_valid_texture = 0;
	game->count_valid_color = 0;
	game->first = 1;
	ft_set_map_color_texture(game);
	ft_check_texture_color_fetch(game, arg);
	set_start_angle_player(game);
	game->map = game->map;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;
	ft_replace_2d(game->map->map2d, '\n', ' ');
	if (mapvalid(game->map->map2d, game->map->h_map, game->map->w_map,
			game) == 0)
	{
		printf("Not Close\n");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
}
