/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:18:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 23:19:12 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	first_check(t_game *game, char **map)
{
	game->i = 0;
	while (map[game->i] != NULL)
	{
		game->j = 0;
		while (map[game->i][game->j] != '\0' && map[game->i][game->j] != '\n')
		{
			if (map[game->i][game->j] == 'N')
			{
				game->player->plyr_y = game->j;
				game->player->plyr_x = game->i;
			}
			if (map[game->i][game->j] == '1' || map[game->i][game->j] == '0'
				|| map[game->i][game->j] == 'N' || map[game->i][game->j] == 32
				|| (map[game->i][game->j] >= 9 && map[game->i][game->j] <= 13)
			|| map[game->i][game->j] == 49 || map[game->i][game->j] == 79)
				game->j++;
			else
			{
				printf("no valid\n");
				exit(27);
			}
		}
		game->i++;
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
		return (-1);
}
