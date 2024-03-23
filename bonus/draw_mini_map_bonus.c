/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:55:46 by ranki             #+#    #+#             */
/*   Updated: 2024/03/23 16:01:40 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../cub3d.h"

void draw_mini_map(t_game *game)
{
    int tileSize = 10; // Taille d'un tile de la mini-carte en pixels
    int margin = 20; // Marge entre la mini-carte et le bord de la fenêtre
    int windowWidth = 800; // À ajuster avec la vraie taille de votre fenêtre
    int windowHeight = 600; // Idem
    
    // Calcul de la position de départ de la mini-carte
    int startX = windowWidth - (game->map->w_map * tileSize) - margin;
    int startY = margin;
    
    // Dessin de la carte
    for (int y = 0; y < game->map->h_map; y++)
    {
        for (int x = 0; x < game->map->w_map; x++)
        {
            int tileColor = game->map->map2d[y][x] == '1' ? 0x000000 : 0xFFFFFF; // Noir pour les murs, blanc pour les espaces
            // Utilisez ici une fonction de MiniLibX pour dessiner chaque tile
            // par exemple, mlx_put_image_to_window() avec une image de tileSize x tileSize pixels
        }
    }
    
    // Dessin du joueur sur la mini-carte
    int playerColor = 0xFF0000; // Rouge pour le joueur
    // Adaptez la position du joueur à la mini-carte et dessinez-le
}