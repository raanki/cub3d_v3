/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:32 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 22:21:17 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_exit(void *param)
{

	exit(0);
}

void	free_game(t_game *game)
{

}

int	ft_reles(int key, t_game *game)
{
	if (key == 65307)
	{
		exit(0);
	}
}

