/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:13 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 18:58:59 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv) {
    
	t_game	*game;
	
	game = game_instance();
	init_map(game);
	start_the_game(game);
    return 0;
}