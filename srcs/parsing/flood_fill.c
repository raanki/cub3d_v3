/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:08:27 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 18:49:36 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int checkLines(char **map, int mapHeight, int mapWidth) {
    for (int i = 0; i < mapHeight; i++) {
        int foundOneFromLeft = 0;
        int foundOneFromRight = 0;
        for (int j = 0; j < mapWidth; j++) {
            if (map[i][j] == '1') {
                foundOneFromLeft = 1;
                break;
            }
            if (map[i][j] == '0' && !foundOneFromLeft) {
                return 0;
            }
        }
        for (int j = mapWidth - 1; j >= 0; j--) {
            if (map[i][j] == '1') {
                foundOneFromRight = 1;
                break;
            }
            if (map[i][j] == '0' && !foundOneFromRight) {
                return 0;
            }
        }
    }
    return 1;
}


int checkColumns(char **map, int mapHeight, int mapWidth) {
    for (int j = 0; j < mapWidth; j++) {
        int foundOneFromTop = 0;
        int foundOneFromBottom = 0;
        for (int i = 0; i < mapHeight; i++) {
            if (map[i][j] == '1') {
                foundOneFromTop = 1;
                break;
            }
            if (map[i][j] == '0' && !foundOneFromTop) {
                return 0;
            }
        }
        for (int i = mapHeight - 1; i >= 0; i--) {
            // De bas en haut
            if (map[i][j] == '1') {
                foundOneFromBottom = 1;
                break;
            }
            if (map[i][j] == '0' && !foundOneFromBottom) {
                return 0;
            }
        }
    }
    return 1;
}


int mapValid(char **map, int mapHeight, int mapWidth) {
    return checkLines(map, mapHeight, mapWidth) && checkColumns(map, mapHeight, mapWidth);
}

