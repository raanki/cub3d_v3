/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:01:31 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 17:37:26 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init_player_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	ft_check_null(game->map);
	game->map->map2d = NULL;
	game->player = malloc(sizeof(t_player));
	ft_check_null(game->player);
	game->sprite_path = ft_calloc(5, sizeof(char *));
	ft_check_null(game->sprite_path);
	game->sprite_path[0] = ft_check_null(ft_strdup("nothing but essential"));
	game->sprite_path[1] = ft_check_null(ft_strdup("nothing but essential"));
	game->sprite_path[2] = ft_check_null(ft_strdup("nothing but essential"));
	game->sprite_path[3] = ft_check_null(ft_strdup("nothing but essential"));
}

int	check_all_texture_is_load(void)
{
	t_game	*game;
	int		i;

	game = ft_game_instance();
	i = 0;
	while (i < 4)
	{
		if (game->valid_texture[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_set_map_color_texture(t_game *g)
{
	while ((g->current_line != NULL && (!check_all_texture_is_load()
				|| g->count_valid_color < 2)) || g->first)
	{
		g->first = 0;
		g->current_line = get_next_line(g->fd);
		if (!g->current_line)
			break ;
		g->cur_tmp = ft_check_null(ft_strdup(g->current_line));
		if (ft_is_line_texture(g->current_line))
		{
			if (g->sprite_path[g->current_sprite])
				ft_free(g->sprite_path[g->current_sprite]);
			g->sprite_path[g->current_sprite] = ft_parse_lt(g->cur_tmp);
			g->count_valid_texture++;
			g->index_sprite_path++;
		}
		else if (ft_is_line_color(g->current_line))
		{
			ft_parse_line_color(g, g->cur_tmp);
			g->count_valid_color++;
		}
		ft_check_map_trade_with_arg(g);
		ft_free(g->cur_tmp);
		ft_free(g->current_line);
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
	game->map = ft_fetch_map_params(game->fd, game->map, arg, game);
	ft_check_null(game->map);
}

//ft_replace_2d(game->map->map2d, '\n', ' ');
void	ft_init_map(t_game *game, char *arg)
{
	ft_init_player_map(game);
	game->fd = ft_open_fd(game, arg);
	game->index_sprite_path = 0;
	game->current_sprite = 0;
	game->count_valid_texture = 0;
	game->count_valid_color = 0;
	game->first = 1;
	ft_set_map_color_texture(game);
	ft_check_texture_color_fetch(game, arg);
	ft_set_start_angle_player(game);
	game->map = game->map;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;
	ft_replace_2d(game->map->map2d, ' ', 'T');
	if (ft_mapvalid(game->map->map2d, game->map->h_map, game->map->w_map,
			game) == 0)
	{
		printf("Not Close\n");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_replace_2d(game->map->map2d, 'T', '1');
}
