/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:57:02 by ranki             #+#    #+#             */
/*   Updated: 2024/03/20 20:39:33 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init_map(t_game *game, char *arg)
{
	t_map		*map;
	t_player	*player;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}

	game->player = malloc(sizeof(t_player));
	if (game->player  == NULL)
	{
		ft_free_game(game);
		exit(0);
	}

//*************************************************************************************************************
    // here do the color / player / texture parsing

	game->sprite_path = ft_calloc(5, sizeof(char *));
	if (!game->sprite_path)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	

	int fd = open_fd(arg);
	char *line = "";
	int	index_sprite_path = 0;
	int	count_valid_information = 0;

    while (line != NULL && count_valid_information < 6)
    {
        line = get_next_line(fd);

		if (is_line_texture(line))
		{
			game->sprite_path[index_sprite_path] = parse_line_texture(game, ft_strdup(line));
			count_valid_information++;
			index_sprite_path++;
		}
		else if (is_line_color(line))
		{
			parse_line_color(game, line);
			count_valid_information++;
		}
        
        free(line);
    }

	game->sprite_path[4] = NULL;
	
// end parse color / player / texture 
//*************************************************************************************************************


	game->map = fetch_map_params(fd, map, arg, game);

	if (!map->map2d)
	{
		ft_free_game(game);
		exit(EXIT_FAILURE);
	}
	game->player ->dir_x = -1;
	game->player ->dir_y = 0;
	game->player ->plan_x = 0;
	game->player ->plan_y = FOV;
	game->map = map;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;

}

void	ft_start_the_game(t_game *game)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit(EXIT_FAILURE);
	game->mlx = mlx;
	game->mlx->mlx_p = mlx_init();
	if (!game->mlx->mlx_p)
	{
		exit (EXIT_FAILURE);
	}
	mlx->win_p = mlx_new_window(mlx->mlx_p, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	ft_load_sprite(game);
	mlx_loop_hook(mlx->mlx_p, &ft_game_loop, game);
	mlx_hook(game->mlx->win_p, KeyRelease, KeyReleaseMask, &ft_reles, game);
	mlx_hook(mlx->win_p, KeyPress, KeyPressMask, ft_mlx_key, game);
	mlx_hook(mlx->win_p, 33, 1L << 17, ft_exit, game);
	mlx_loop(mlx->mlx_p);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
