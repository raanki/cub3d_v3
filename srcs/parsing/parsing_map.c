/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:22 by ranki             #+#    #+#             */
/*   Updated: 2024/03/21 21:22:17 by mklimina         ###   ########.fr       */
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
	// map->map2d[map -> h_map] = NULL;
	while (i < map -> h_map +1)
	{
		map->map2d[i] = ft_calloc(map -> w_map + 1, sizeof(char));
		memset(map->map2d[i], ' ', map->w_map);
		i++;
	}

	for (int z = 0; map->map2d[z]; z++)
		printf("[%i]{%s}\n", z, map->map2d[z]);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		// printf("[%s]\n", line);
		// printf("line -> %s\n", !line);
		if (!line)
			break ;
		if (is_line_color(line) || is_only_space(line)  || is_line_texture(line)) 
		{
			free(line);
			line = NULL;
			continue ;
		}
		strncpy(map->map2d[i], line, ft_strlen(line));
		if (line)
		{
			free(line);
			line = NULL;
		}
		i++;
	}
	
	for (int z = 0; map->map2d[z]; z++)
		printf("AFTER[%i]{%s}\n", z, map->map2d[z]);
	close(fd);
	// ft_free_game(game);
	// exit(1);
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
			return (123);
	}
	else
	{
		if (line[i] == '1')
			return (0);
		else
			return (145);
	}
}

t_map	*test_map(t_game *game, t_map *map)
{
	int		i;
	char	**check_map;
	int		flag;
	int		flag_1;

	flag = -1;
	i = 0;
	check_map = map ->map2d;
	first_check(game, map -> map2d);
	while (check_map[i] != NULL)
	{
		if (i == 0 || i == map->h_map - 1)
		{
			flag = scan_first_last_line(check_map[i], i, check_map, map);
			printf("FLAG ERROR %i\n", flag);
			if (flag > 0)
			{
				printf("Map is not valid here\n");
				ft_free_game(game);
				exit(27);
			}
		}
		else
		{
			flag = stupid_count_one_algo(check_map[i], i, check_map);
			flag_1 = stupid_count_one_algo_right(check_map[i], i, check_map);
			printf("FLAG %i FLAG_1 %i\n", flag, flag_1);
			if (flag > 0 || flag_1 > 0)
			{
				printf("Map is not valid there\n");
				ft_free_game(game);
				exit(27);
			}
		}
		flag = -1;
		i++;
	}
	return (map);
}
