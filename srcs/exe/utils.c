/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:25 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 19:01:20 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int char_to_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else
    {
        return -1;
    }
}

t_game	*game_instance(void)
{
	static t_game	*game_instance;

	if (game_instance == NULL)
	{
		game_instance = calloc(1, sizeof(t_game));
		if (!game_instance)
			exit(0);
		game_instance->map = NULL;
		game_instance->player = NULL;
	}
	return (game_instance);
}