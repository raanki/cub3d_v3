/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:54:44 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 00:38:10 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

char    *remove_first_spaces_until_first_letter(char *line)
{
	int     index_first_character;
	int     index_last_space;
	char    *ret;

	index_first_character = 0;
	index_last_space = 0;
	if (!line)
		return line;
	while(line[index_last_space] == ' ')
		index_last_space++;
	if (!index_last_space)
		return line;
	ret = ft_strdup(line + index_last_space);
	if (!ret)
	{
		ft_e_str("malloc");
		return NULL;
	}
	return (ret);

}

int    is_line_color(char *line)
{
	char    *cpy_line;
	
	if (!line || line[0] == '\0')
		return (0);
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (!ft_strncmp(cpy_line, "F ", 2)
		|| !ft_strncmp(cpy_line, "C ", 2))
		return (1);
	return (0);
}


char	*get_type_texture_from_valid_line_color(char *line)
{
	char *ret;

	ret = malloc(2 + 1);
	if (!ret)
	{
		ft_e_str("malloc");
		return NULL;
	}
	ret[0] = line[0];
	ret[1] = line[1];
	ret[2] = '\0';
	return (ret);
}

char *remove_last_spaces(char *line)
{
	int index_last_letter;
	int	i;
	char *ret;
	int size_line = 0;
	
	size_line = ft_strlen(line);
	index_last_letter = size_line - 1;
	i = 0;
	while ((line[index_last_letter] == ' ' || line[index_last_letter] == '\n') && index_last_letter >= 0)
		index_last_letter--;
	if (index_last_letter < 0) 
		return line;
	index_last_letter++;
	ret = malloc(2 * size_line - index_last_letter + 1);
	if (!ret)
	{
		ft_e_str("malloc");
		return NULL;
	}
	while (i < index_last_letter)
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char *remove_all_space(char *str)
{
	int i;
	int size_str;
	int size_return;
	char *ret;

	size_return = 0;
	i = 0;
	size_str = ft_strlen(str);
	if (!size_str){
		return NULL;
	}
	while(str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			size_return++;
		i++;
	}
	ret = malloc(size_str - size_return + 1);
	if (!ret)
	{
		return 0;
	}
	i = 0;
	int index_new_str = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			ret[index_new_str] = str[i];
			index_new_str++;	
		}
		i++;
	}
	ret[index_new_str] = '\0';
	return ret;
}

unsigned int rgb_to_hex(int r, int g, int b)
{
    unsigned int hex;
    hex = (r << 16) + (g << 8) + b;
    return hex;
}

char	*get_color_from_valid_line_color(char *line)
{
	char *color_str;

	color_str = remove_first_spaces_until_first_letter(line + 2);
	return (color_str);
	
}



unsigned int	parse_line_color(t_game *game, char *line)
{
	char	*cpy_line;
	char	*type_text;
	char	*path;
	int r, g, b;
	char	**split_rgb;
	int		color_ceilling = 0;
	int i = 0;

	if (!is_line_color(line))
	{
		ft_e_str("not valid line color");
		return 0;
	}
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (line && (line[0] == 'C'))
	{
		color_ceilling = 1;
	}
	cpy_line = get_color_from_valid_line_color(cpy_line);
	cpy_line = remove_all_space(cpy_line);
	split_rgb = ft_split(cpy_line, ',');
	while(split_rgb && split_rgb[i])
	{
		if (i == 0)
			r = atoi(split_rgb[0]);
		if (i == 1)
			g = atoi(split_rgb[1]);
		if (i == 2)
			b = atoi(split_rgb[2]);
		i++;
	}

	if (color_ceilling) {
		game->color_ceilling = rgb_to_hex(r, g , b);
		printf("set color for ceilling\n");
	} else {
		game->color_floor = rgb_to_hex(r, g , b);
		printf("set color for floor");
	}
	return rgb_to_hex(r, g , b);
}





