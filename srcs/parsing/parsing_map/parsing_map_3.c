/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:18:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 22:45:46 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	set_good_angle_with_letter(t_game *game, char c)
{
	if (c == 'N')
		game->angle_player = 3;
	if (c == 'S')
		game->angle_player = 1;
	if (c == 'E')
		game->angle_player = 0;
	if (c == 'W')
		game->angle_player = 2;
}

void	ft_check_spawn_wall_nothing_any(t_game *game, char **map)
{
	if (map[game->i][game->j] == 'N' || map[game->i][game->j] == 'S'
			|| map[game->i][game->j] == 'E' || map[game->i][game->j] == 'W')
	{
		game->player->plyr_y = game->i + 0.5;
		game->player->plyr_x = game->j + 0.5;
		set_good_angle_with_letter(game, map[game->i][game->j]);
		printf("heigth = %d\n", game->map->h_map);
		printf("width = %d\n", game->map->w_map);
		map[game->i][game->j] = '0';
		game->number_player_letter_find++;
	}
	if ((map[game->i][game->j] == '1' || map[game->i][game->j] == '0'
		|| map[game->i][game->j] == 32
		|| (map[game->i][game->j] >= 9 && map[game->i][game->j] <= 13)
	|| map[game->i][game->j] == 49 || map[game->i][game->j] == 79))
		game->j++;
	else
	{
		ft_free_game(game);
		printf("no valid\n");
		exit(27);
	}
}

void	first_check(t_game *game, char **map)
{
	game->i = 0;
	game->number_player_letter_find = 0;
	while (map[game->i] != NULL)
	{
		game->j = 0;
		while (map[game->i][game->j] != '\0' && map[game->i][game->j] != '\n')
			ft_check_spawn_wall_nothing_any(game, map);
		game->i++;
	}
	if (game->number_player_letter_find != 1)
	{
		ft_free_game(game);
		printf("You have to put only 1 player\n");
		exit(27);
	}
}

void	condition_stupid_count_one_algo(int *cnt,
		int line_curr, char **map, int i)
{
	if (map[line_curr + 1][i - 1] == '1'
			|| map[line_curr + 1][i + 1] == '1' || map[line_curr + 1][i] == '1')
		cnt++;
	if (map[line_curr + 1][i] == '1'
			|| map[line_curr - 1][i] == '1' || map[line_curr - 1][i - 1] == '1')
		cnt++;
	if ((map[line_curr + 1][i - 1] == '1'
		&& map[line_curr - 1][i + 1] == '1')
			|| (map[line_curr - 1][i + 1] == '1'
				&& map[line_curr + 1][i - 1] == '1'))
		cnt++;
}

int	stupid_count_one_algo(char *line, int line_curr, char **map)
{
	int	i;
	int	cnt;
	int	is_ws;

	i = -1;
	cnt = 0;
	is_ws = 0;
	while (line[++i] == 32 || (line[i] >= 9 && line[i] <= 13))
		is_ws = 1;
	if (is_ws == 1 && line[i] == '1')
	{
		condition_stupid_count_one_algo(&cnt, line_curr, map, i);
		if (cnt >= 2)
			return (0);
		else
			return (1);
	}
	else
		if (line[i] == '1')
			return (0);
	else
		return (1);
}
