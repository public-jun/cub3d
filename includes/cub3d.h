/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:49:26 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/17 18:00:17 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>

# define MAP_HEIGHT 50
# define MAP_WIDTH 50
# define R 0
# define G 1
# define B 2

typedef struct		s_win_r
{
	int				x;
	int				y;
}					t_win_r;

typedef struct		s_path_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_path_tex;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				rgb;
}					t_color;

typedef struct		s_map
{
	char			char_map[MAP_HEIGHT][MAP_WIDTH];
	int				map[MAP_HEIGHT][MAP_WIDTH];
	int				start;
	int				end;
	int				tmp_y;
	int				pflag;
}					t_map;

typedef struct		s_flag
{
	int				eflag;
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
	int				except_map;
}					t_flag;

typedef struct		s_all
{
	// t_info		info;
	// t_img		img;
	// t_player	player;
	// t_info		info;
	// t_key		key;
	// t_pair		pair;
	// t_sprite	sprite;
	t_win_r		win_r;
	t_path_tex		path_tex;
	t_color			color_f;
	t_color			color_c;
	t_map			map;
	t_flag			flag;
}					t_all;

#endif
