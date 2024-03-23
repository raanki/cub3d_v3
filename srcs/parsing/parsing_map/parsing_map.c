/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:22 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 14:21:48 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	ft_condition_count_one_algo(char *line, int line_curr,
		char **map, t_game *game)
{
	game->has_next_line = (map[line_curr + 1] != NULL);
	game->has_prev_line = (line_curr > 0);
	if (game->i > 0 && line[game->i - 1] == '1')
		game->cnt++;
	if (line[game->i + 1] == '1')
		game->cnt++;
	if (game->has_next_line)
	{
		if (game->i > 0 && map[line_curr + 1][game->i - 1] == '1')
			game->cnt++;
		if (map[line_curr + 1][game->i] == '1')
			game->cnt++;
		if (map[line_curr + 1][game->i + 1] == '1')
			game->cnt++;
	}
	if (game->has_prev_line)
	{
		if (game->i > 0 && map[line_curr - 1][game->i - 1] == '1')
			game->cnt++;
		if (map[line_curr - 1][game->i] == '1')
			game->cnt++;
		if (map[line_curr - 1][game->i + 1] == '1')
			game->cnt++;
	}
}

int	stupid_count_one_algo_right(char *line, int line_curr, char **map)
{
	t_game	*game;

	game = ft_game_instance();
	game->is_ws = 0;
	game->cnt = 0;
	game->i = strlen(line);
	while (--game->i >= 0 && (line[game->i] == 32
			|| (line[game->i] >= 9 && line[game->i] <= 13)))
		game->is_ws = 1;
	if (game->is_ws == 1 && line[game->i] == '1')
	{
		ft_condition_count_one_algo(line, line_curr, map, game);
		if (game->cnt >= 2)
			return (0);
		else
			return (1);
	}
	else
	{
		if (line[game->i] == '1')
			return (0);
		else
			return (1);
	}
}

void	ft_condition_test_map(t_game *game, t_map *map)
{
	if (game->i == 0 || game->i == map->h_map - 1)
	{
		game->flag = scan_first_last_line(game->check_map[game->i],
				game->i, game->check_map, map);
		if (game->flag == 1)
		{
			ft_e_str("Map is not valid\n");
			ft_free_game(game);
			exit(27);
		}
	}
	else
	{
		game->flag = stupid_count_one_algo(game->check_map[game->i],
				game->i, game->check_map);
		game->flag_1 = stupid_count_one_algo_right(game->check_map[game->i],
				game->i, game->check_map);
		if (game->flag == 1 || game->flag_1 == 1)
		{
			ft_e_str("Map is not valid\n");
			ft_free_game(game);
			exit(27);
		}
	}
	game->flag = -1;
}

t_map	*test_map(t_game *game, t_map *map)
{
	game->flag = -1;
	game->i = 0;
	game->check_map = map ->map2d;
	first_check(game, map -> map2d);
	while (game->check_map[game->i] != NULL)
	{
		ft_condition_test_map(game, map);
		game->i++;
	}
	return (map);
}
