/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:34:29 by ranki             #+#    #+#             */
/*   Updated: 2024/03/21 23:42:48 by ranki            ###   ########.fr       */
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

char	*remove_first_spaces_until_first_letter(char *line)
{
	int		index_first_character;
	int		index_last_space;
	char	*ret;

	index_first_character = 0;
	index_last_space = 0;
	if (!line)
		return (line);
	while (line[index_last_space] == ' ')
		index_last_space++;
	if (!index_last_space)
		return (line);
	ret = ft_strdup(line + index_last_space);
	if (!ret)
	{
		ft_e_str("malloc");
		return (NULL);
	}
	free(line);
	return (ret);
}

int	ft_str_have_three_coma(char *string)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (string && string[i])
	{
		if (string[i] == ',' && string[i + 1] != ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	is_line_color(char *line)
{
	char	*cpy_line;

	if (!line || line[0] == '\0')
		return (0);
	if (!ft_str_have_three_coma(line))
	 	return (0);
	cpy_line = remove_first_spaces_until_first_letter(line);
	if (!ft_strncmp(cpy_line, "F ", 2)
		|| !ft_strncmp(cpy_line, "C ", 2))
	{
		return (1);
	}
	return (0);
}

char	*get_type_texture_from_valid_line_color(char *line)
{
	char	*ret;

	ret = malloc(2 + 1);
	if (!ret)
	{
		ft_e_str("malloc");
		return (NULL);
	}
	ret[0] = line[0];
	ret[1] = line[1];
	ret[2] = '\0';
	free(line);
	return (ret);
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (r << 16) + (g << 8) + b;
	return (hex);
}
