/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:07:23 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 14:43:02 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

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
			printf("\"%c\" ", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	open_fd(t_game *game, char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_e_str("File not found");
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
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

int	scan_first_last_line(char *line, int line_curr, char **map, t_map *map_info)
{
	int	i;
	int	is_ws;

	is_ws = 0;
	i = -1;
	while (line[++i] == 32 || (line[i] >= 9 && line[i] <= 13))
		is_ws = 1;
	if (is_ws == 1 && line[i] == '1' && line_curr == 0)
		if (map[line_curr + 1][i - 1] != '1')
			return (1);
	if (is_ws == 1 && line[i] == '1' && line_curr == map_info -> h_map - 1)
		if (map[line_curr - 1][i - 1] != '1')
			return (1);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && (line[i] != 32
				|| (line[i] >= 9 && line[i] <= 13) == 1))
			return (1);
		i++;
	}
	return (0);
}
