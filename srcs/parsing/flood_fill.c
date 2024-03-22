/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:08:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 19:00:16 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int checkLines(char **map, int mapHeight, int mapWidth)
{
	int i = 0;
	while (i < mapHeight)
	{
		int foundOneFromLeft = 0;
		int j = 0;
		while (j < mapWidth) {
			if (map[i][j] == '1')
			{
				foundOneFromLeft = 1;
				break;
			}
			if (map[i][j] == '0' && !foundOneFromLeft)
			{
				return 0;
			}
			j++;
		}

		int foundOneFromRight = 0;
		j = mapWidth - 1;
		while (j >= 0)
		{
			if (map[i][j] == '1')
			{
				foundOneFromRight = 1;
				break;
			}
			if (map[i][j] == '0' && !foundOneFromRight)
			{
				return 0;
			}
			j--;
		}
		i++;
	}
	return 1;
}



int checkColumns(char **map, int mapHeight, int mapWidth)
{
	int j = 0;
	while (j < mapWidth)
	{
		int foundOneFromTop = 0;
		int i = 0;
		while (i < mapHeight) {
			if (map[i][j] == '1') {
				foundOneFromTop = 1;
				break;
			}
			if (map[i][j] == '0' && !foundOneFromTop)
			{
				return 0;
			}
			i++;
		}

		int foundOneFromBottom = 0;
		i = mapHeight - 1;
		while (i >= 0)
		{
			if (map[i][j] == '1')
			{
				foundOneFromBottom = 1;
				break;
			}
			if (map[i][j] == '0' && !foundOneFromBottom)
			{
				return 0;
			}
			i--;
		}
		j++;
	}
	return 1;
}

int is_adjacent_valid(char **map, int x, int y, int mapHeight, int mapWidth) 
{
	int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int i = 0;
	while (i < 4)
	{
		int newX = x + dirs[i][0];
		int newY = y + dirs[i][1];
		if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight)
		{
			if (map[newY][newX] != '1' && map[newY][newX] != '0')
			{
				return 0;
			}
		}
		i++;
	}
	return 1;
}

int checkMap(char **map, int mapHeight, int mapWidth)
{
	int i = 0;
	while (i < mapHeight)
	{
		int j = 0;
		while (j < mapWidth) {
			if (map[i][j] == '0')
			{
				if (!is_adjacent_valid(map, j, i, mapHeight, mapWidth))
				{
					return 0;
				}
			}
			j++;
		}
		i++;
	}
	return 1;
}


int mapValid(char **map, int mapHeight, int mapWidth)
{
	return checkLines(map, mapHeight, mapWidth) && checkColumns(map, mapHeight, mapWidth) && checkMap(map, mapHeight, mapWidth);
}

