/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:55:01 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 20:54:59 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

int	is_line_texture(char *line)
{
	char	*cpy_line;

	if (!line || line[0] == '\0')
		return (0);
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (!ft_strncmp(cpy_line, "NO ", 3)
		|| !ft_strncmp(cpy_line, "SO ", 3)
		|| !ft_strncmp(cpy_line, "WE ", 3)
		|| !ft_strncmp(cpy_line, "EA ", 3))
	{
		return (1);
	}
	return (0);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_path_from_valid_line_texture(char *line)
{
	char	*path_line;

	path_line = remove_first_spaces_until_first_letter(line + 3);
	return (path_line);
}

char	*parse_line_texture(t_game *game, char *line)
{
	char	*cpy_line;
	char	*type_text;
	char	*path;

	if (!is_line_texture(line))
	{
		ft_e_str("not valid line color");
		return (NULL);
	}
	cpy_line = remove_first_spaces_until_first_letter(line);
	cpy_line = get_path_from_valid_line_texture(cpy_line);
	cpy_line = remove_last_spaces(cpy_line);
	return (cpy_line);
}