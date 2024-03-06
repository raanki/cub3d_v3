/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:22 by ranki             #+#    #+#             */
/*   Updated: 2024/03/03 18:04:58 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void prnt(char** arr) {
    int i = 0;
    while (arr[i] != NULL) {
        int j = 0;
        while (arr[i][j] != '\0') {
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

int is_line_bigger(char *str, int old_len)
{
    int new_len;

    if (str)
         new_len = strlen(str);
    if (old_len == -1)
        return(new_len);
    else
    {
        if (old_len > new_len)
            return(old_len);
        else
            return(new_len);
    }
    return (old_len);
}

t_map *create_map(t_map *map, char *file)
{
    int fd;
    int i = 0;
    fd = open_fd(file);
    map->map2d = ft_calloc(map -> h_map + 1, sizeof(char *));
    map->map2d[map -> h_map] = NULL;

    while (i < map -> h_map)
    {
        map->map2d[i] = ft_calloc(map -> w_map + 1, sizeof(char));
        int j = 0;
        while (j < map -> w_map) {
            map->map2d[i][j] = 32;
            j++;
        }
        i++;
    }
    i = 0;
    while(True)
    {
        char *line = get_next_line(fd);
        if (map->map2d[i] == NULL)
            break;
        strncpy(map->map2d[i], line, strlen(line));
        i++;
    }
    //prnt(map -> map2d);
    return (map);
}

//t_map *test_map(t_map *map)
//{
//
//}

t_map *fetch_map_params(t_map *map, char *file)
{
    int fd;
    char *line = "";
    int width;
    int i = 0;
    fd = open_fd(file);

    width = -1;
    while (line != NULL)
    {
        line = get_next_line(fd);

        if (line) {
            width = is_line_bigger(line, width);
            i++;
        }
        free(line);
    }
    close(fd);
    //printf("    len -> %d", i);
    map -> w_map = width;
    map -> h_map = i;

    map = create_map(map, file);

    return(map);
}

void	ft_parse_map(t_game *game)
{
	(void)game;
}