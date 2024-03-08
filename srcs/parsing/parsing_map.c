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

//int check_map_values(char c)
//{
//    if (c != 32 || c != 48 || c != 49)
//}

int scan_first_last_line(char *line, int line_curr, char **map)
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
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (line[i] != '1' && (line[i] != 32 || (line[i] >= 9 && line[i] <= 13) == 1))
            return(1);
        i++;
    }
    return(0);
}

int stupid_count_one_algo_left(char *line, int line_curr, char **map)
{
    int i = 0;
    int cnt = 0;
    int is_ws = 0;
    //skip whitespaces
    //printf("line num %d -> %s\n", i,line);

    while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)){
        i++;
        is_ws = 1;
    }

    if (is_ws == 1 && line[i] == '1')
    {
        printf("ws\n");
        if (map[line_curr+1][i - 1] == '1' || map[line_curr+1][i + 1] == '1'  || map[line_curr+1][i] == '1')
            cnt++;
        if (map[line_curr+1][i] == '1' || map[line_curr-1][i] == '1' || map[line_curr-1][i - 1] == '1')
            cnt++;
        if ((map[line_curr+1][i - 1] == '1' && map[line_curr-1][i + 1] == '1') || (map[line_curr-1][i + 1] == '1' && map[line_curr+1][i - 1] == '1'))
            cnt++;
        printf("cnt -> %d", cnt);
        if (cnt >= 2)
            return(0);
        else
            return(1);
    }
    else
    {
        //printf("else\n");
        if (line[i] == '1')
            return(0);
        else
            return(-1);
    }


}

t_map *test_map(t_map *map)
{
    int i;
    char **check_map;
    int flag;
    flag = -1;
    i = 0;
    check_map = map ->map2d;

    while (check_map[i] != NULL)
    {
        if (i == 0 || i == map->h_map - 1)
        {
            flag = scan_first_last_line(check_map[i], i, check_map);
            if (flag == 1)
            {
                printf("Map is not valid/scan");
                //printf("line num %d -> %s\n", i,check_map[i]);
                // free stuff
                exit(27);
            }
        }
        else
        {
            flag = stupid_count_one_algo_left(check_map[i], i, check_map);
            //printf("line -> %s flag -> %d, i -> %d\n", check_map[i], flag, i);
            if (flag == 1)
            {
                printf("Map is not valid/algo");
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