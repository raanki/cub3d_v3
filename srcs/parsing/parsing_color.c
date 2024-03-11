/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:54:44 by ranki             #+#    #+#             */
/*   Updated: 2024/03/09 12:28:44 by ranki            ###   ########.fr       */
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

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i < n)
	{
		i++;
	}
	if (i >= n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	if (!ft_strncmp(cpy_line, "NO ", 3)
		|| !ft_strncmp(cpy_line, "SO ", 3)
			|| !ft_strncmp(cpy_line, "WE ", 3)
				|| !ft_strncmp(cpy_line, "EA ", 3))
		return (1);
	return (0);
}


char	*get_path_from_valid_line_color(char *line)
{
	char *path_line;

	path_line = remove_first_spaces_until_first_letter(line + 3);
	return (path_line);
	
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

	index_last_letter = 0;
	i = 0;
	while (line[index_last_letter] != ' ' && line[index_last_letter] != '\0')
		index_last_letter++;
	ret = malloc(ft_strlen(line) - index_last_letter + 1);
	if (!ret)
	{
		ft_e_str("malloc");
		return NULL;
	}
	while (i <= index_last_letter)
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void    parse_line_color(t_game *game, char *line)
{
	char	*cpy_line;
	char	*type_text;
	char	*path;

	if (!is_line_color(line))
	{
		ft_e_str("not valid line color");
		return ;
	}
	cpy_line = remove_first_spaces_until_first_letter(line);
	cpy_line = get_path_from_valid_line_color(cpy_line);
	printf("path line : \"%s\"\n", cpy_line);
	cpy_line = remove_last_spaces(cpy_line);
	printf("remove last parameters : \"%s\"\n", cpy_line);
		
}