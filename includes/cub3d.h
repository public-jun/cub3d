/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:49:26 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/23 15:14:31 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "struct.h"
# include "define.h"
# include "../libft/libft.h"
# include "../minilibx_mms_20200219/mlx.h"
//mac
// # include "key_macos.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>

int				main(int ac, char **av);
void			ft_init_all(t_all *all);
void			ft_init(t_all *all);
void			ft_free_path(t_all *all);
void			ft_exit(t_all *all, char **line);
void			ft_put_error_and_exit(t_all *all, char **line, char *s);
int				ft_skip_null_and_space(char **line, int *i);
int				ft_is_all_num(char *num);
void			ft_parse_line_r(t_all *all, char **line);
void			ft_parse_line_path(t_all *all, char **path, int *flag, char **line);
void			ft_parse_line_color(t_all *all, t_color *color, int *flag, char **line);
void			ft_parse_line_param(t_all *all, char **line);
int				ft_flag_on_expect_map(t_all *all);
void			ft_store_sprite_player_coordinate(t_all *all, char **line, int y, int x);
void			ft_store_line_with_map(t_all *all, char **line);
void			ft_judge_possible_chars(t_all *all, char **line);
int				ft_in_the_process_of_forming_map(t_all *all, char **line);
void			ft_parse_line_map(t_all *all, char **line);
void			ft_parse_line(t_all *all, char **line);
void			ft_read_cub(int fd, t_all *all);
void			ft_flood_fill(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y);
void			ft_store_sprite_coordinate(t_all *all, int x, int y);
void			ft_store_player_dir(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y);
void			ft_store_player_info(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y);
void			ft_get_info_from_map(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH]);
void			ft_mlx_and_raycast_init(t_all *all);
void			ft_combine_input_and_output(t_all *all);
void			set_texture_in_load_image(t_all *all, int i);
void			load_image(t_all *all, char *path);
void			ft_load_texture(t_all *all);
int				ft_min(int a, int b);
void			floor_and_ceilling_casting(t_all *all);
void			ft_set_ray_data(t_all *all, t_ray *ray, t_player *player, int x);
void			ft_check_raydir_and_set_sidedist(t_ray *ray, t_player *player);
void			ft_find_collision_with_wall(t_ray *ray, t_map *map, t_player *player);
void			ft_calculate_wall_height_on_screen(t_all *all, t_ray *ray);
void			ft_set_direction_tex(t_ray *ray, t_tex *tex);
void			ft_attach_tex_size_for_screen(t_all *all, t_ray *ray, t_player *player, t_tex *tex);
void			ft_set_buf(t_ray *ray, t_tex *tex, t_info *info, int x);
void			ft_wall_casting(t_all *all);
int				ft_raycasting(t_all *all);

#endif
