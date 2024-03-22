/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:22 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 13:46:34 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_map	*create_map(t_game *game, t_map *map, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	i = 0;
	fd = open_fd(game, file);
	map->map2d = ft_calloc(map -> h_map + 1, sizeof(char *));
	map->map2d[map -> h_map] = NULL;
	while (i < map -> h_map)
	{
		map->map2d[i] = ft_calloc(map -> w_map + 1, sizeof(char));
		j = 0;
		while (j < map -> w_map)
		{
			map->map2d[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (is_line_color(line) || is_line_texture(line) || is_only_space(line))
		{
			free(line);
			line = NULL;
			continue ;
		}
		if (!line)
		{
			while (i < map -> h_map)
			{
				free(map->map2d[i]);
				map->map2d[i] = NULL;
				i++;
			}
			free(map->map2d[i]);
			map->map2d[i] = NULL;
			break ;
		}
		strncpy(map->map2d[i], line, ft_strlen(line));
		if (line)
		{
			free(line);
			line = NULL;
		}
		i++;
	}
	close(fd);
	return (map);
}

int	stupid_count_one_algo_right(char *line, int line_curr, char **map)
{
	int	i;
	int	cnt;
	int	is_ws;
	int	has_next_line;
	int	has_prev_line;

	is_ws = 0;
	cnt = 0;
	i = strlen(line) - 1;
	while (i >= 0 && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
	{
		i--;
		is_ws = 1;
	}
	if (is_ws == 1 && line[i] == '1')
	{
		has_next_line = (map[line_curr + 1] != NULL);
		has_prev_line = (line_curr > 0);
		if (i > 0 && line[i - 1] == '1')
			cnt++;
		if (line[i + 1] == '1')
			cnt++;
		if (has_next_line)
		{
			if (i > 0 && map[line_curr + 1][i - 1] == '1')
				cnt++;
			if (map[line_curr + 1][i] == '1')
				cnt++;
			if (map[line_curr + 1][i + 1] == '1')
				cnt++;
		}
		if (has_prev_line)
		{
			if (i > 0 && map[line_curr - 1][i - 1] == '1')
				cnt++;
			if (map[line_curr - 1][i] == '1')
				cnt++;
			if (map[line_curr - 1][i + 1] == '1')
				cnt++;
		}
		if (cnt >= 2)
			return (0);
		else
			return (1);
	}
	else
	{
		if (line[i] == '1')
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
			printf("Map is not valid\n");
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
			printf("Map is not valid\n");
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
