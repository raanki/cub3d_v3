/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:16:07 by ranki             #+#    #+#             */
/*   Updated: 2024/04/06 13:04:28 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//****************************************************************
//****************************************************************
//******************************* INCLUDES ***********************
//****************************************************************
//****************************************************************

# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//****************************************************************
//****************************************************************
//******************************** DEFINES ***********************
//****************************************************************
//****************************************************************

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 400
# define M_PI 3.14159265358979323846
# define TILE_SIZE 64
# define FOV 0.66
# define PLAYER_COLOR 0xFF0000
# define OFFSET_X 20
# define OFFSET_Y 20
# define EMPTY_IN_MINIMAP 0x000000
# define WALL_OUT_MINIMAP 0xFFFFFF
# define TILE_SIZE_MINIMAP 5
# define COLOR_LINE_MINIMAP 0x9400D3
# define MAX_HEIGHT_MAP 500
# define MAX_WIDTH_MAP 500

# include "srcs/gnl/get_next_line.h"
//*****************************************************************
//*****************************************************************
//******************************* STUCTURES ***********************
//*****************************************************************
//*****************************************************************

typedef struct s_map
{
	char			**map2d;
	int				w_map;
	int				h_map;
	double			time;
	double			old_time;
}					t_map;

typedef struct s_player
{
	double			plyr_x;
	double			plyr_y;
	double			dir_x;
	double			dir_y;
	double			plan_x;
	double			plan_y;
}					t_player;

typedef struct s_mlx
{
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx_p;
	void			*win_p;
	void			*img;
}					t_mlx;

typedef struct s_sprite
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				*pixel_colors;
}					t_sprite;

typedef struct s_game
{
	t_map			*map;
	t_player		*player;
	t_mlx			*mlx;
	t_sprite		**sprite;
	double			camera_x;
	double			camera_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			move_speed;
	double			sure_mode;
	double			rot_speed;
	double			rot_speed_mouse;
	double			step_side;
	double			sure_mode_h;
	int				map_player_x;
	int				map_player_y;
	int				pitch;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				hit;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				color;
	int				b;
	int				r;
	int				g;
	int				i;
	int				j;
	int				is_ceilling;
	int				number_player_letter_find;
	int				angle_player;
	int				current_sprite;
	int				index_sprite_path;
	int				count_valid_texture;
	int				count_valid_color;
	int				first;
	int				fd;
	int				flag;
	int				flag_1;
	int				cnt;
	int				is_ws;
	int				has_next_line;
	int				has_prev_line;
	int				now_is_map;
	int				index_spaces;
	int				x_prev_mouse;
	int				mouse_is_press;
	int				tile_size_minimap;
	int				offset_x;
	int				offset_y;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	int				range;
	int				msm;
	int				is_bonus;
	char			**sprite_path;
	char			*cpy_line;
	char			*type_text;
	char			*path;
	char			**split_rgb;
	char			*current_line;
	char			*cur_tmp;
	char			**check_map;
	char			*line;
	char			*arg;
	char			*save;
	int				valid_texture[4];
	int				dirs[4][2];
	unsigned int	color_ceilling;
	unsigned int	color_round;
	unsigned int	buffer[SCREEN_HEIGHT + 1][SCREEN_WIDTH + 1];
}	t_game;

//************************************************************
//************************************************************
//**************************** FUNCTIONS *********************
//************************************************************
//************************************************************

//************************************************************
//************************* EXE ******************************
//************************************************************

t_game				*ft_game_instance(void);
double				ft_nor_angle(double angle);
int					ft_reles(int key, t_game *game);
int					ft_exit(void *param);
int					ft_char_to_int(char c);
int					ft_mlx_key(int key, void *gam);
int					ft_game_loop(void);
int					ft_find_nice_pitch(void);
int					ft_check_res(t_game *game);
int					ft_exit(void *param);
int					ft_atoi(char *s);
int					ft_which_wall(t_game *game, double ray_angle, int side);
void				ft_start_the_game(t_game *game);
void				ft_init_map(t_game *game, char *args);
void				ft_load_sprite(t_game *game);
void				ft_free_game(t_game *game);
void				ft_hook(t_game *game);
void				ft_my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				ft_hook_init_side_dist(t_game *game);
void				ft_hook_find_hit(t_game *game);
void				ft_hook_init_loop(t_game *game, int x);
void				ft_hook_target_draw(t_game *game);
void				ft_hook_find_text_x_y(t_game *game);
void				*ft_calloc(size_t count, size_t size);
void				ft_e_str(char *s);
void				ft_free_mlx(t_game *game);
void				ft_free_map(t_game *game, int *i);
void				ft_rotate_left(int key, t_game *game);
void				ft_rotate_right(int key, t_game *game);
void				ft_draw_minimap_direction(t_game *game);
void				ft_calc_pos_minimap(int x, int y, int color);
void				ft_condition_draw_line(t_game *game, int *y0, int *x0);

//************************************************************
//************************* PARSING **************************
//************************************************************

t_map				*ft_fetch_map_params(int fd, t_map *map, char *file_name,
						t_game *game);
t_map				*ft_test_map(t_game *game, t_map *map);
t_map				*ft_create_map(t_game *game, t_map *map, char *file);
unsigned int		ft_parse_line_color(t_game *game, char *line);
unsigned int		ft_rgb_to_hex(int r, int g, int b);
char				*ft_parse_lt(char *line);
char				*ft_remove_last_spaces(char *line);
char				*ft_remove_first_spaces_until_first_letter(char *line);
char				**ft_split(char const *s, char c);
int					ft_is_line_color(char *line);
int					ft_is_only_space(char *str);
int					ft_is_line_texture(char *line);
int					ft_open_fd(t_game *game, char *name);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_valid_char(char *line);
int					ft_mapvalid(char **map, int mapHeight, int mapWidth,
						t_game *game);
int					ft_check_column_from_top(char **map, int mapHeight, int j);
int					ft_check_column_from_bottom(char **map,
						int mapHeight, int j);
int					ft_check_line_from_left(char **map, int mapWidth, int i);
int					ft_check_line_from_right(char **map, int mapWidth, int i);
int					ft_is_only_c_f_number(char *line);
int					ft_str_have_three_coma(char *string);
int					ft_is_line_bigger(char *str, int old_len);
int					ft_find_last_non_whitespace_char(char *line);
int					check_all_texture_is_load(void);
int					ft_scan_first_last_line(char *line, int line_curr,
						char **map, t_map *map_info);
int					ft_stupid_count_one_algo(char *line, int line_curr,
						char **map);
int					ft_index_first_letter(char *line);
void				ft_set_array_flood(t_game *game);
void				ft_check_map_trade_with_arg(t_game *game);
void				ft_free(void *ptr);
void				*ft_check_null(void *ptr);
void				ft_check_read(char *stash, char *buffer, int fd, int ret);
void				ft_first_check(t_game *game, char **map);
void				ft_set_start_angle_player(t_game *game);
void				ft_check_invalid_char_map(t_game *game);
void				ft_replace_2d(char **array, char to_find, char to_replace);
void				ft_prnt(char **arr);
void				ft_check_max_size(int i, int width, t_game *game);

//BONUS

int					ft_mouse_moove(int x, int y, void *param);
int					ft_mouse_press(int button, int x, int y, void *game);
int					ft_mouse_release(int button, int x, int y, void *game);
void				ft_draw_minimap(void);
void				ft_launch_hook(void);

#endif