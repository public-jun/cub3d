/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:21 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/22 21:29:48 by jnakahod         ###   ########.fr       */
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
	int				int_map[MAP_HEIGHT][MAP_WIDTH];
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

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;
}					t_img;

typedef struct		s_info
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				**buf;
	double			zBuffer[width];
	int				**texture;
	double			moveSpeed;
	double			rotSpeed;
}					t_info;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct		s_key
{
	int				a;
	int				w;
	int				s;
	int				d;
	int				esc;
	int				left;
	int				right;
}					t_key;

typedef struct		s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			prepwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
}					t_ray;

typedef struct		s_sprite
{
	int				sp_x;
	int				sp_y;
	double			distance;
}					t_sprite;

typedef struct		s_sprite_info
{
	int				num;
	t_sprite		*order;
	int				tmp;
}					t_sprite_info;

typedef struct		s_all
{
	t_img			img;
	t_info			info;
	t_player		player;
	t_key			key;
	t_sprite		sprite;
	t_sprite_info	sprite_info;
	t_win_r			win_r;
	t_path_tex		path_tex;
	t_color			color_f;
	t_color			color_c;
	t_map			map;
	t_flag			flag;
	t_ray			ray;
}					t_all;

#endif
