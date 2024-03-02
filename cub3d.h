/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:26 by ranki             #+#    #+#             */
/*   Updated: 2024/03/02 19:51:04 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//****************************************************************
//****************************************************************
//******************************* INCLUDES ***********************
//****************************************************************
//****************************************************************

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
#include <stdbool.h>

//****************************************************************
//****************************************************************
//******************************** DEFINES ***********************
//****************************************************************
//****************************************************************

#define mapWidth 24 
#define mapHeight 24 
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480
# define TILE_SIZE 64
# define SPRITE_WEST "sprites/one.xpm"
# define SPRITE_EAST "sprites/two.xpm"
# define SPRITE_NORTH "sprites/four.xpm"
# define SPRITE_SOUTH "sprites/three.xpm"

//*****************************************************************
//*****************************************************************
//******************************* STUCTURES ***********************
//*****************************************************************
//*****************************************************************

typedef struct s_map
{
	char	**map2d;
	int		w_map;
	int		h_map;
	double  time;
	double old_time;
	
}	t_map;

typedef struct s_player
{
	double		plyr_x;
	double		plyr_y;
    double     dir_x;
    double     dir_y;
    double     plan_x;
    double     plan_y;
	
}	t_player;

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	void	*mlx_p;
	void	*win_p;
	int		endian;
}	t_mlx;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int     *pixel_colors;
}	t_sprite;


typedef struct s_game
{
	t_map *map;
	t_player *player;
	t_mlx *mlx;
	t_sprite	**sprite;
	int		buffer[SCREEN_HEIGHT + 1][SCREEN_HEIGHT + 1];
	double camera_x;
	double camera_y;
	double ray_dir_x;
	double ray_dir_y;
	int map_player_x;
	int map_player_y;
	double sideDistX;
    double sideDistY;
	double deltaDistX;
    double deltaDistY;
    double perpWallDist;
	int stepX;
    int stepY;
    int side;
	int hit;
	
}	t_game;


//************************************************************
//************************************************************
//**************************** FUNCTIONS *********************
//************************************************************
//************************************************************

//************************************************************
//************************* EXE ******************************
//************************************************************

void	load_sprite(t_game *game);
void draw_sprite_column(t_game *game, int screen_x, int start, int end, int sprite_x, int which);
void	free_game(t_game *game);
int	ft_reles(int key, t_game *game);
int	ft_exit(void *param);
int char_to_int(char c);
t_game	*game_instance(void);
void	start_the_game(t_game *game);
int init_map(t_game *game);
int	ft_mlx_key(int key, void *gam);
int	game_loop(void);
void	hook(t_game *game, double move_x, double move_y);
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
