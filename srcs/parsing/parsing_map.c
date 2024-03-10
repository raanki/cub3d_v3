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
    close(fd);
    //prnt(map -> map2d);
    return (map);
}


int scan_first_last_line(char *line, int line_curr, char **map, t_map *map_info)
{
    int i;
    int is_ws = 0;
    i = 0;

    while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
    {
        is_ws = 1;
        i++;
    }
    if (is_ws == 1 && line[i] == '1' && line_curr == 0)
    {
        if (map[line_curr + 1][i - 1] != '1')
            return(1);
    }
    if (is_ws == 1 && line[i] == '1' && line_curr == map_info -> h_map - 1)
    {
        if (map[line_curr - 1][i - 1] != '1')
        {

            return(1);
        }

    }
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (line[i] != '1' && (line[i] != 32 || (line[i] >= 9 && line[i] <= 13) == 1))
            return(1);
        i++;
    }
    return(0);
}

int stupid_count_one_algo(char *line, int line_curr, char **map)
{
    int i = 0;
    int cnt = 0;
    int is_ws = 0;

    while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)){
        i++;
        is_ws = 1;
    }

    if (is_ws == 1 && line[i] == '1')
    {

        if (map[line_curr+1][i - 1] == '1' || map[line_curr+1][i + 1] == '1'  || map[line_curr+1][i] == '1')
            cnt++;
        if (map[line_curr+1][i] == '1' || map[line_curr-1][i] == '1' || map[line_curr-1][i - 1] == '1')
            cnt++;
        if ((map[line_curr+1][i - 1] == '1' && map[line_curr-1][i + 1] == '1') || (map[line_curr-1][i + 1] == '1' && map[line_curr+1][i - 1] == '1'))
            cnt++;

        if (cnt >= 2)
            return(0);
        else
            return(1);
    }
    else
    {
        if (line[i] == '1')
            return(0);
        else
            return(-1);
    }
}

int find_last_non_whitespace_char(char *line) {
    int i = strlen(line) - 1;
    while (i >= 0 && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))) {
        i--;
    }
    return i;
}

int stupid_count_one_algo_right(char *line, int line_curr, char **map) {
    int i = strlen(line) - 1;
    int cnt = 0;
    int is_ws = 0;

    // make this into a separate func return i -> then resuse it
    while (i >= 0 && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))) {
        i--;
        is_ws = 1;
    }

    if (is_ws == 1 && line[i] == '1') {
        int has_next_line = (map[line_curr + 1] != NULL);
        int has_prev_line = (line_curr > 0);

        if (i > 0 && line[i - 1] == '1')
            cnt++;
        if (line[i + 1] == '1')
            cnt++;

        if (has_next_line) {
            if (i > 0 && map[line_curr + 1][i - 1] == '1')
                cnt++;
            if (map[line_curr + 1][i] == '1')
                cnt++;
            if (map[line_curr + 1][i + 1] == '1')
                cnt++;
        }
        if (has_prev_line) {
            if (i > 0 && map[line_curr - 1][i - 1] == '1')
                cnt++;
            if (map[line_curr - 1][i] == '1')
                cnt++;
            if (map[line_curr - 1][i + 1] == '1')
                cnt++;
        }

        if (cnt >= 2)
            return(0);
        else
            return(1);
    }
    else {
        if (line[i] == '1')
            return(0);
        else
            return(-1);
    }
}
void first_check(char **map)
{
    int i;
    int j;
    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while (map[i][j] != '\0' && map[i][j] != '\n')
        {
            if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 32 || (map[i][j] >= 9 && map[i][j] <= 13))
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

t_map *test_map(t_map *map)
{
    int i;
    char **check_map;
    int flag;
    int flag_1;
    flag = -1;
    i = 0;
    check_map = map ->map2d;

    first_check(map -> map2d);

    // complex check spaces
    while (check_map[i] != NULL)
    {
        if (i == 0 || i == map->h_map - 1)
        {
            flag = scan_first_last_line(check_map[i], i, check_map, map);
            if (flag == 1)
            {

                printf("Map is not valid hih");
                // exit
                exit(27);
            }
        }
        else
        {
            flag = stupid_count_one_algo(check_map[i], i, check_map);
            flag_1 = stupid_count_one_algo_right(check_map[i], i, check_map);
            if (flag == 1 || flag_1 == 1)
            {
                printf("Map is not valid");
                // free stuff
                exit(27);
            }
        }
        flag = -1;
        i++;
    }


    // test first line it should be all 1
    // all till last one -> first and last char should be 1

    // last line -> all 1
    printf("map ok");
    return(map);
}

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
    map -> w_map = width;
    map -> h_map = i;
    map = create_map(map, file);
    //prnt(map -> map2d);
    map = test_map(map);
    return(map);

}

void	ft_parse_map(t_game *game)
{
	(void)game;
}