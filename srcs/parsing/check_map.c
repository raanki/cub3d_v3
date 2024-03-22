/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:49:21 by ranki             #+#    #+#             */
/*   Updated: 2024/03/22 17:51:52 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_replace_2d(char **array, char to_find, char to_replace)
{
	int	i;
	int	j;

	i = 0;
	while (array && array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == to_find)
				array[i][j] = to_replace;
			j++;
		}
		i++;
	}
}
