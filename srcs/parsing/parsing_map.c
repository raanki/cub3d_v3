/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:22 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 22:56:05 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	prnt(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			printf("%c ", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	open_fd(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit(0);
	return (fd);
}

int	is_line_bigger(char *str, int old_len)
{
	int	new_len;

	if (str)
		new_len = strlen(str);
	if (old_len == -1)
		return (new_len);
	else
	{
		if (old_len > new_len)
			return (old_len);
		else
			return (new_len);
	}
	return (old_len);
}

t_map	*create_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	i = 0;
	fd = open_fd(file);
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
			free(map->map2d[i]);
			map->map2d[i] = NULL;
			i++;
			while (i < map -> h_map)
			{
				free(map->map2d[++i]);
			}
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

int	scan_first_last_line(char *line, int line_curr, char **map, t_map *map_info)
{
	int	i;
	int	is_ws;

	is_ws = 0;
	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
	{
		is_ws = 1;
		i++;
	}
	if (is_ws == 1 && line[i] == '1' && line_curr == 0)
	{
		if (map[line_curr + 1][i - 1] != '1')
			return (1);
	}
	if (is_ws == 1 && line[i] == '1' && line_curr == map_info -> h_map - 1)
	{
		if (map[line_curr - 1][i - 1] != '1')
			return (1);
	}
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && (line[i] != 32
				|| (line[i] >= 9 && line[i] <= 13) == 1))
			return (1);
		i++;
	}
	return (0);
}

int	stupid_count_one_algo(char *line, int line_curr, char **map)
{
	int	i;
	int	cnt;
	int	is_ws;

	i = 0;
	cnt = 0;
	is_ws = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
	{
		i++;
		is_ws = 1;
	}
	if (is_ws == 1 && line[i] == '1')
	{
		if (map[line_curr + 1][i - 1] == '1' || map[line_curr + 1][i + 1] == '1' || map[line_curr + 1][i] == '1')
			cnt++;
		if (map[line_curr + 1][i] == '1' || map[line_curr - 1][i] == '1' || map[line_curr - 1][i - 1] == '1')
			cnt++;
		if ((map[line_curr + 1][i - 1] == '1' && map[line_curr - 1][i + 1] == '1') || (map[line_curr - 1][i + 1] == '1' && map[line_curr+1][i - 1] == '1'))
			cnt++;
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
			return (-1);
	}
}

int	find_last_non_whitespace_char(char *line)
{
	int	i;

	i = strlen(line) - 1;
	while (i >= 0 && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
	{
		i--;
	}
	return (i);
}

int	stupid_count_one_algo_right(char *line, int line_curr, char **map)
{
	int i;
	int cnt;
	int is_ws;
	int has_next_line;
	int has_prev_line;

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
			return (-1);
	}
}

void	first_check(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0' && map[i][j] != '\n')
		{
			if (map[i][j] == 'N')
			{
				game->player->plyr_y = j;
				game->player->plyr_x = i;
			}
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'N'
			|| map[i][j] == 32 || (map[i][j] >= 9 && map[i][j] <= 13)
			|| map[i][j] == 49 || map[i][j] == 79)
				j++;
			else
			{
				printf("no valid\n");
				exit(27);
			}
		}
		i++;
	}
	printf("All valid\n");
}

t_map *test_map(t_game *game, t_map *map)
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
			if (flag == 1)
			{
				printf("Map is not valid\n");
				ft_free_game(game);
				exit(27);
			}
		}
		else
		{
			flag = stupid_count_one_algo(check_map[i], i, check_map);
			flag_1 = stupid_count_one_algo_right(check_map[i], i, check_map);
			if (flag == 1 || flag_1 == 1)
			{
				printf("Map is not valid\n");
				ft_free_game(game);
				exit(27);
			}
		}
		flag = -1;
		i++;
	}
	return (map);
}

t_map	*fetch_map_params(int fd, t_map *map, char *file, t_game *game)
{
	char	*line;
	int		width;
	int		i;

	i = 0;
	line = "";
	width = -1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line)
		{
			width = is_line_bigger(line, width);
			i++;
		}
		free(line);
	}
	close(fd);
	map -> w_map = width;
	map -> h_map = i;
	map = create_map(map, file);
	map = test_map(game, map);
	return (map);
}
