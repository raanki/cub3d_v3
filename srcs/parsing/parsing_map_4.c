/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:27:53 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 13:31:00 by ranki            ###   ########.fr       */
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
	map = create_map(game, map, file);
	map = test_map(game, map);
	return (map);
}

char	*remove_last_spaces(char *line)
{
	int		index_last_letter;
	int		i;
	char	*ret;
	int		size_line;

	size_line = 0;
	size_line = ft_strlen(line);
	index_last_letter = size_line - 1;
	while ((line[index_last_letter] == ' ' || line[index_last_letter] == '\n')
		&& index_last_letter >= 0)
		index_last_letter--;
	if (index_last_letter < 0)
		return (line);
	index_last_letter++;
	ret = malloc(2 * size_line - index_last_letter + 1);
	if (!ret)
		return (ft_e_str("malloc"), NULL);
	i = -1;
	while (++i < index_last_letter)
		ret[i] = line[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (cpy == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
