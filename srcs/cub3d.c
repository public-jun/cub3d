/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:03:09 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/10 11:03:43 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define N_TEX 0
#define S_TEX 1
#define E_TEX 2
#define W_TEX 3
#define SP_TEX 4
#define numSprites 8

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_player;

typedef struct	s_info
{
	void		*mlx;
	void		*win;
	int			**buf;
	double		zBuffer[width];
	int			**texture;
	double		moveSpeed;
	double		rotSpeed;
}				t_info;

typedef struct	s_key
{
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	int			key_esc;
}				t_key;

typedef struct		s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_all
{
	t_info		info;
	t_img		img;
	t_player	player;
	t_info		info;
	t_key		key;
	t_pair		pair;
	t_sprite	sprite;
}				t_all;

int				main(void)
{
	t_all		all;
	
}
