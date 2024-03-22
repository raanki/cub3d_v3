/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:08:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 21:34:32 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	checklines(char **map, int mapHeight, int mapWidth)
{
	int	i;

	i = 0;
	while (i < mapHeight)
	{
		if (!check_line_from_left(map, mapWidth, i)
			|| !check_line_from_right(map, mapWidth, i))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_adjacent_valid(char **map, int x, int y, t_game *game)
{
	int	i;
	int	new_x;
	int	new_y;
	int	dirs[4][2];

	dirs[0][0] = 0;
	dirs[0][1] = -1;
	dirs[1][0] = 0;
	dirs[1][1] = 1;
	dirs[2][0] = -1;
	dirs[2][1] = 0;
	dirs[3][0] = 1;
	dirs[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		new_x = x + dirs[i][0];
		new_y = y + dirs[i][1];
		if (new_x >= 0 && new_x < game->map->w_map && new_y >= 0
			&& new_y < game->map->h_map)
		{
			if (map[new_y][new_x] != '1' && map[new_y][new_x] != '0')
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	checkcolumns(char **map, int mapHeight, int mapWidth)
{
	int	j;

	j = 0;
	while (j < mapWidth)
	{
		if (!check_column_from_top(map, mapHeight, j)
			|| !check_column_from_bottom(map, mapHeight, j))
		{
			return (0);
		}
		j++;
	}
	return (1);
}

int	checkmap(char **map, int mapHeight, int mapWidth, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			if (map[i][j] == '0')
			{
				if (!is_adjacent_valid(map, j, i, game))
				{
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	mapvalid(char **map, int mapHeight, int mapWidth, t_game *game)
{
	return (checklines(map, mapHeight, mapWidth) && checkcolumns(map, mapHeight,
			mapWidth) && checkmap(map, mapHeight, mapWidth, game));
}
