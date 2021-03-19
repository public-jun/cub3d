/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:21 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/19 21:09:34 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "cub3d.h"
#include "define.h"

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
	int				p_x;
	int				p_y;
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


// typedef struct	s_info
// {
// 	double	posX;
// 	double	posY;
// 	double	dirX;
// 	double	dirY;
// 	double	planeX;
// 	double	planeY;
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// 	int		**buf;
// 	double	zBuffer[width];
// 	int		**texture;
// 	double	moveSpeed;
// 	double	rotSpeed;
// }				t_info;

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
