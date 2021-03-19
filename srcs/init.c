/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:23:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/19 21:01:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//init struct all
void			ft_init_all(t_all *all)
{
	all->flag.eflag = 0;
	all->flag.r = 0;
	all->flag.no = 0;
	all->flag.so = 0;
	all->flag.we = 0;
	all->flag.ea = 0;
	all->flag.s = 0;
	all->flag.f = 0;
	all->flag.c = 0;
	all->flag.except_map = 0;
	all->win_r.x = 0;
	all->win_r.y = 0;
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;
	all->map.pflag = 0;
	all->map.start = 0;
	all->map.end = 0;
	all->map.tmp_y = 1;
	all->map.p_x = 0;
	all->map.p_y = 0;
}

void			ft_init_char_map(t_all *all)
{
	int			x;
	int			y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
				all->map.char_map[y][x] = 'x';
			else
				all->map.char_map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void			ft_init(t_all *all)
{
	ft_init_all(all);
	ft_init_char_map(all);
}
