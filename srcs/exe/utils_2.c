/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:13:50 by ranki             #+#    #+#             */
/*   Updated: 2024/03/25 23:44:09 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_check_end_file(char *str)
{
	int	size_str;

	if (!str)
		return (0);
	size_str = ft_strlen(str);
	if (size_str < 5)
		return (0);
	size_str--;
	while (size_str >= 0 && str[size_str] != '.')
	{
		size_str--;
	}
	if (size_str == 0)
		return (0);
	if (!ft_strncmp(str + size_str, ".cub", 4))
		return (1);
	return (0);
}

int	check_all_texture_is_load(void)
{
	t_game	*game;
	int		i;

	game = ft_game_instance();
	i = 0;
	while (i < 4)
	{
		if (game->valid_texture[i] == 0)
			return (0);
		i++;
	}
	return (1);
}
